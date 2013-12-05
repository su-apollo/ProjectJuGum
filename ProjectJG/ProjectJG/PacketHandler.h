#pragma once
#include "PacketType.h"
#include "NNBaseHandler.h"
#include "NNCircularBuffer.h"

class CPacketHandler : public NNBaseHandler
{
public:
	CPacketHandler(void);
	virtual ~CPacketHandler(void);

	void HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header );

	PacketKeyStatus m_PacketKeyStatus;
};
