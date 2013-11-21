#pragma once

#include "GameOption.h"
#include "PacketType.h"

class NNP2PNetHelper
{
public:
	NNP2PNetHelper(bool serverMode, char* serverAddr) ;
	~NNP2PNetHelper() ;

	bool Initialize() ;

	/// 2 컴퓨터간 통신 확인
	bool DoHandShake() ;

	bool IsPeerLinked() const { return m_IsPeerLinked ; }
	bool IsServerMode() const { return m_IsServerMode ; }

	bool SendKeyStatus(const PacketKeyStatus& sendKeys) ;
	bool RecvKeyStatus(OUT PacketKeyStatus& recvKeys) ;

	EInputSetUp UpdateStateByPeerInput(int frameNum) ;
	void		SendKeyStateToPeer(int frameNum, EInputSetUp inputsetup);

private:

	bool			m_IsServerMode ;
	bool			m_IsPeerLinked ;

	SOCKET			m_Socket ;
	SOCKADDR_IN		m_PeerAddrIn ;
	int				m_PeerAddrLen ;

	char			m_TargetAddr[MAX_STRING] ;
} ;


extern NNP2PNetHelper* GNetHelper ;

