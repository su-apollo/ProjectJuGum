#include "NNConfig.h"
#include "PacketHandler.h"


CPacketHandler::CPacketHandler(void)
{
}


CPacketHandler::~CPacketHandler(void)
{
}

void CPacketHandler::HandlingPacket( short packetType, NNCircularBuffer* circularBuffer, NNPacketHeader* header )
{
	switch ( packetType )
	{
	case PKT_STATUS:
		{
			if ( !circularBuffer->Read((char*)&m_PacketKeyStatus, header->m_Size) )
			{
				assert(false) ;
			}
		}
		break;
	}
}