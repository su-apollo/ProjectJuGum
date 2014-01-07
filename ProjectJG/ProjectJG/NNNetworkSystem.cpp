#include "NNConfig.h"

#include "NNNetworkSystem.h"
#include "NNApplication.h"
#include "PacketType.h"

NNNetworkSystem* NNNetworkSystem::m_pInstance = nullptr;

NNNetworkSystem::NNNetworkSystem()
	: m_ServerIP(nullptr), m_Port(SERVER_PORT_NUM), 
	m_RecvBuffer(NNCircularBuffer(1024*4)),
	m_SendBuffer(NNCircularBuffer(1024*4))
{
}
NNNetworkSystem::~NNNetworkSystem()
{
	Destroy();
}

bool NNNetworkSystem::Init()
{
	WSADATA WsaDat ;

	int nResult = WSAStartup(MAKEWORD(2,2),&WsaDat) ;
	if ( nResult != 0 )
		return false ;

	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) ;
	if ( m_Socket == INVALID_SOCKET )
		return false ;

	nResult = WSAAsyncSelect(NNNetworkSystem::GetInstance()->m_Socket, NNApplication::GetInstance()->GetHWND(), WM_SOCKET,(FD_CLOSE|FD_CONNECT|FD_ACCEPT));
	if (nResult)
	{
		MessageBox(NNApplication::GetInstance()->GetHWND(), L"WSAAsyncSelect failed", L"Critical Error", MB_ICONERROR);
		SendMessage(NNApplication::GetInstance()->GetHWND(),WM_DESTROY,NULL,NULL);
		return false;
	}

	return true ;
}

void NNNetworkSystem::Destroy()
{
	//소캣을 클로우즈 해야함
	closesocket(m_Socket);

	for (auto& iter=m_PacketHandler.begin(); iter!=m_PacketHandler.end(); iter++ )
	{
		SafeDelete( iter->second );
	}
	m_PacketHandler.clear();
}

bool NNNetworkSystem::Connect( const char* serverIP, int port )
{
	// Resolve IP address for hostname
	struct hostent* host ;

	if ( (host=gethostbyname(serverIP) ) == NULL )
		return false ;

	// Set up our socket address structure
	SOCKADDR_IN SockAddr ;
	SockAddr.sin_port = htons(port) ;
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr) ;

	if ( SOCKET_ERROR == connect(m_Socket, (LPSOCKADDR)(&SockAddr), sizeof(SockAddr)) )
	{
		if (GetLastError() != WSAEWOULDBLOCK )
			return false ;
	}

	return true ;
}

int NNNetworkSystem::Listen(int port)
{
	// 	int opt = 1 ;
	// 	::setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(int) ) ;

	/// bind
	SOCKADDR_IN serveraddr ;
	ZeroMemory(&serveraddr, sizeof(serveraddr)) ;
	serveraddr.sin_family = AF_INET ;
	serveraddr.sin_port = htons(port) ;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY) ;
	int ret = bind(m_Socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) ;
	if (ret == SOCKET_ERROR)
		return -1 ;

	/// listen
	ret = listen(m_Socket, SOMAXCONN) ;
	if (ret == SOCKET_ERROR)
		return -1 ;
	SOCKET acceptSocket;
	while (true)
	{
		acceptSocket = accept(m_Socket, NULL, NULL);
		if ( acceptSocket == INVALID_SOCKET )
		{
			printf("accept: invalid socket\n") ;
			continue;
		}

		m_Socket = acceptSocket;
		break;
	}
	return 0;
}

void NNNetworkSystem::ProcessPacket()
{
	while ( true )
	{
		NNPacketHeader header;

		if ( m_RecvBuffer.Peek((char*)&header, sizeof(NNPacketHeader)) == false )
		{
			break;
		}

		//임시방편적으로 워닝을 잡기위한 형변환
		if ( (unsigned short)header.m_Size > m_RecvBuffer.GetCurrentSize() )
		{
			break;
		}

		m_PacketHandler[header.m_Type]->HandlingPacket(header.m_Type, &m_RecvBuffer, &header);
	}
}

void NNNetworkSystem::Write( const char* data, size_t size )
{
	if ( m_SendBuffer.Write(data, size) )
	{
		PostMessage(NNApplication::GetInstance()->GetHWND(), WM_SOCKET, NULL, FD_WRITE) ;
	}
}

void NNNetworkSystem::Read()
{
	char inBuf[4096] = {0, } ;

	int recvLen = recv(m_Socket, inBuf, 4096, 0) ;

	if ( !m_RecvBuffer.Write(inBuf, recvLen) )
	{
		/// 버퍼 꽉찼다. 
		//assert(false) ;
	}
	else
	{
		ProcessPacket() ;
	}
}

void NNNetworkSystem::SetPacketHandler( short packetType, NNBaseHandler* handler )
{
	m_PacketHandler[packetType] = handler;
}

NNNetworkSystem* NNNetworkSystem::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new NNNetworkSystem();
	}

	return m_pInstance;
}
void NNNetworkSystem::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
	}
}

char* NNNetworkSystem::GetIpAddress()
{
	char myaddr[256];
	PHOSTENT pHostInfo;
	in_addr in;

	//로컬pc의 호스트이름을 표준양식으로받아옴(MSDN)
	gethostname(myaddr, sizeof(myaddr));   

	printf_s("myaddr : %s\n", myaddr);

	//호스트이름에 대응되는Databas를 PHOSTENT구조체로 리턴
	pHostInfo = gethostbyname(myaddr);           

	if( pHostInfo != NULL )     
	{ 
		in.s_addr = ( ( LPIN_ADDR ) pHostInfo->h_addr )->s_addr; 
		m_ServerIP = inet_ntoa( in );
	}

	return m_ServerIP;
}


