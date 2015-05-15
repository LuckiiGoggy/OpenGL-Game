// Client: ClientGame.cpp
//

#include "ClientGame.h"

using namespace GLNetwork;

ClientGame::ClientGame()
{
	network = new ClientNetwork();

	// send init packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}


ClientGame::~ClientGame(void)
{
}

void ClientGame::sendActionPackets(int i)
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::update(int j)
{
	Packet packet;
	int data_length = network->receivePackets(network_data);

	if (data_length <= 0)
	{
		//no data recieved
		return;
	}

	int i = 0;
	while (i < (unsigned int)data_length)
	{
		packet.deserialize(&(network_data[i]));
		i += sizeof(Packet);

		switch (packet.packet_type) {

		case ACTION_EVENT:

			printf("client received action event packet from server\n");

			sendActionPackets(j);

			break;

		default:

			printf("error in packet types\n");

			break;
		}
	}
}
