#include "GLNetwork.h"



GLNetwork::Packet::Packet() : packet_type(ACTION_EVENT), packet_size(sizeof(Packet))
{

}

GLNetwork::Packet::Packet(PacketType packetType, size_t packetSize) 
	: packet_type(packetType), packet_size(packetSize)
{

}
