#include "NNConfig.h"
#include "NetManager.h"


NetHelper* GNetHelper = NULL ;

NetHelper::NetHelper(bool serverMode, char* serverAddr) : m_PeerAddrLen(0), m_Socket(NULL), m_IsServerMode(serverMode), m_IsPeerLinked(false)
{
	strcpy_s(m_TargetAddr, serverAddr) ;
}

NetHelper::~NetHelper()
{
	closesocket(m_Socket) ;
	WSACleanup() ;
}


bool NetHelper::Initialize()
{
	/// Socket 초기화 
	WSADATA wsa ;
	if ( WSAStartup(MAKEWORD(2, 2), &wsa) != 0 )
		return false ;

	m_Socket = socket(AF_INET, SOCK_DGRAM, 0) ;
	if (m_Socket == INVALID_SOCKET)
		return false ;

	return true ;
}


bool NetHelper::DoHandShake()
{
	//클라->서버
	//서버->클라
	//2handshake
	char ioBuf[BUF_SIZE] = {0, } ;

	SOCKADDR_IN serveraddr ;
	ZeroMemory(&serveraddr, sizeof(serveraddr)) ;
	serveraddr.sin_family = AF_INET ;
	serveraddr.sin_port = htons(SERVER_PORT_NUM) ;

	if (m_IsServerMode)
	{

		BOOL on = TRUE ;
		//소켓을 설정
		int retval = setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) ;
		if (retval == SOCKET_ERROR)
			return false ;

		//순서를 네트워크에 맞게 조정(빅 에디안)
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY) ;
		//소켓에게 ip와 포트번호를 부여
		retval = bind(m_Socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) ;
		if (retval == SOCKET_ERROR)
			return false ;


		m_PeerAddrLen = sizeof(m_PeerAddrIn) ;
		//클라이언트의 접속을 기다린다.
		retval = recvfrom(m_Socket, ioBuf, BUF_SIZE, 0, (SOCKADDR*)&m_PeerAddrIn, &m_PeerAddrLen) ;
		if (retval == SOCKET_ERROR)
		{
			MessageBox(NULL, L"ERROR: first recvfrom()", L"ERROR", MB_OK) ;
			return false ;
		}

		//버퍼에 연결되었는지 확인하는 값이 들어왔는지 확인
		if (!strncmp(ioBuf, "CONNECT", 7))
		{
			sprintf_s(ioBuf, "SUCCESS") ;
			//확인했음을 클라이언트에게 전송
			retval = sendto(m_Socket, ioBuf, strlen(ioBuf), 0, (SOCKADDR*)&m_PeerAddrIn, sizeof(m_PeerAddrIn)) ;
			if (retval == SOCKET_ERROR)
			{
				MessageBox(NULL, L"ERROR: sendto(SUCCESS)", L"ERROR", MB_OK) ;
				return false ;
			}

			m_IsPeerLinked = true ;
		}
		else
		{
			MessageBox(NULL, L"ERROR: INVALID CONNECT!!", L"ERROR", MB_OK) ;
			return false ;
		}

	}
	else
	{
		serveraddr.sin_addr.s_addr = inet_addr(m_TargetAddr) ;

		BOOL on = TRUE ;
		//소캣설정을 타임아웃으로 설정
		int retval = setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&on, sizeof(on)) ;
		if (retval == SOCKET_ERROR)
			return false ;

		//버퍼에 확인하는 값을 복사
		sprintf_s(ioBuf, "CONNECT");
		//서버에게 전송
		retval = sendto(m_Socket, ioBuf, strlen(ioBuf), 0, (SOCKADDR*)&serveraddr, sizeof(serveraddr)) ;
		if (retval == SOCKET_ERROR)
		{
			MessageBox(NULL, L"ERROR: first sendto(CONNECT)", L"ERROR", MB_OK) ;
			return false ;
		}

		m_PeerAddrLen = sizeof(m_PeerAddrIn) ;
		//서버에서 확인했음을 확인
		retval = recvfrom(m_Socket, ioBuf, BUF_SIZE, 0, (SOCKADDR*)&m_PeerAddrIn, &m_PeerAddrLen) ;
		if (retval == SOCKET_ERROR)
		{
			MessageBox(NULL, L"ERROR: recvfrom(SUCCESS)", L"ERROR", MB_OK) ;
			return false ;
		}

		if (!strncmp(ioBuf, "SUCCESS", 7))
		{
			m_IsPeerLinked = true ;
		}
		else
		{
			//백신끄고 할것
			MessageBox(NULL, L"ERROR: INVALID SERVER!!", L"ERROR", MB_OK) ;
			return false ;
		}
	}

	return true ;
}


bool NetHelper::SendKeyStatus(const PacketKeyStatus& sendKeys)
{

	/// SEND
	int retval = sendto(m_Socket, (char*)&sendKeys, sizeof(PacketKeyStatus), 0, (SOCKADDR*)&m_PeerAddrIn, sizeof(m_PeerAddrIn)) ;
	if (retval == SOCKET_ERROR)
	{
		MessageBox(NULL, L"ERROR: sendto() in LOOP!", L"ERROR", MB_OK) ;
		return false ;
	}

	return true ;
}

bool NetHelper::RecvKeyStatus(OUT PacketKeyStatus& recvKeys)
{
	/// RECEIVE
	int retval = recvfrom(m_Socket, (char*)&recvKeys, sizeof(PacketKeyStatus), 0, (SOCKADDR*)&m_PeerAddrIn, &m_PeerAddrLen) ;
	if (retval == SOCKET_ERROR)
	{
		MessageBox(NULL, L"ERROR: recvfrom() in LOOP!", L"ERROR", MB_OK) ;
		return false ;
	}

	return true ;
}

void NetHelper::GetHostIP()
{
	char myaddr[256];
	PHOSTENT pHostInfo;
	char *pTemp;

	IN_ADDR in;

	//로컬pc의 호스트이름을 표준양식으로받아옴(MSDN)
	gethostname(myaddr, sizeof(myaddr));

	//호스트이름에 대응되는Databas를 PHOSTENT구조체로 리턴
	pHostInfo = gethostbyname(myaddr); 
	
	if( pHostInfo != NULL )     
	{ 
		in.s_addr = ( ( LPIN_ADDR ) pHostInfo->h_addr )->s_addr; 
		pTemp = inet_ntoa( in ); // 문자열로 변환된 IP주소를 얻을수 있다.
	} 
	else 
	{ 
		MessageBox(NULL, L"ERROR: GetHostIP Error!", L"ERROR", MB_OK) ;
	}

	printf_s("%s", pTemp);
}
