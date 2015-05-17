// Client: ClientGame.cpp
//

#include "ClientGame.h"

using namespace GLNetwork;

ClientGame::ClientGame()
{
	network = new ClientNetwork();

	char *packet_data;

	Packet *packet = new Packet();

	const unsigned int packet_size = PacketBuilder::SerializePacket(INIT_CONNECTION, packet, packet_data);
	//packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}


ClientGame::~ClientGame(void)
{
}

void ClientGame::sendActionPackets(int i)
{
	// send action packet
	char *packet_data;

	PlayerPacket packet;
	
	//packet.forward = true;
	/packet.isShooting = true;

	const unsigned int packet_size = PacketBuilder::SerializePacket(PLAYER_PACKET, &packet, packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::update(int j)
{
	Packet *packet;
	PlayerInfoPacket newPacket;
	int data_length = network->receivePackets(network_data);
	int packetSize = 0;
	if (data_length <= 0)
	{
		//no data recieved
		return;
	}

	int i = 0;
	for(int i =0; i < (unsigned int)data_length; i+=packetSize)
	{

		packetSize = PacketReader::DeSerializePacket(packet, network_data, i);

		switch (network_data[i]) {

		case ACTION_EVENT:

			printf("client received action event packet from server\n");
			break;

		case PLAYER_INFO_PACKET:

			printf("\nPlayer Info, objID: %d, ammo: %d, health: %d, score: %d", ((PlayerInfoPacket *)packet)->objectId,((PlayerInfoPacket *)packet)->ammo, ((PlayerInfoPacket *)packet)->health, ((PlayerInfoPacket *)packet)->score);



			sendActionPackets(j);

			break;

		default:

			printf("error in packet types\n");

			break;
		}
	}
}
