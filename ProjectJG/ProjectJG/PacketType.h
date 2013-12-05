#pragma once
#include "NNConfig.h"
#include "NNPacketHeader.h"

#define MAX_STRING		128

#define BUF_SIZE			32
#define SERVER_PORT_NUM	9001

#define SHOT_PACKET_TIME 0.03f

enum PacketTypes
{
	PKT_NONE	= 0,
	PKT_TEST	= 1,
	PKT_STATUS	= 2,
};

#define MAX_PAYLOAD	512
#define MAX_KEY_TYPE	256

#pragma pack(push, 1)

struct PacketTest
{
	PacketTest() : mType(PKT_TEST), mSequence(-1)
	{
		memset(mPayLoad, 0, MAX_PAYLOAD) ;
	}

	short	mType;
	int		mSequence;
	char	mPayLoad[MAX_PAYLOAD] ;
} ;

struct PacketKeyStatus : public NNPacketHeader
{
	PacketKeyStatus() : mHitCheck(false), 
		mDirectionStatus(0), mSkillStatus(0)
	{
		m_Type = PKT_STATUS; 
		m_Size = sizeof(PacketKeyStatus);
	}

	bool	mHitCheck ;
	short	mDirectionStatus;
	short	mSkillStatus;
	short	mSpeedStatus;
} ;

#pragma pack(pop)