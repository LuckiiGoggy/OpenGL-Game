// Server: ServerGame.cpp
//

#include "ServerGame.h"
#include <iostream>

unsigned int ServerGame::client_id = 0;
ServerNetwork* ServerGame::network = new ServerNetwork();

using namespace GLNetwork;

ServerGame::ServerGame(void)
{
	// Assigning id's to clients
	client_id = 0;

	// Setup network for listening
	//network = new ServerNetwork();
}

ServerGame::~ServerGame(void)
{
}

void ServerGame::update()
{
	// Get clients
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);

		myThreads.push_back(new std::thread(threadedClient, client_id));

		client_id++;

	}

	//receiveFromClients();
	sendActionPackets();
}

void ServerGame::receiveFromClients()
{

	Packet packet;

	// Iterate through all clients
	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = network->sessions.begin(); iter != network->sessions.end(); iter++)
	{
		int data_length = network->receiveData(iter->first, network_data);

		if (data_length <= 0)
		{
			//no data recieved
			continue;
		}

		int i = 0;
		while (i < (unsigned int)data_length)
		{
			packet.deserialize(&(network_data[i]));
			i += sizeof(Packet);

			switch (packet.packet_type) {

			case INIT_CONNECTION:

				printf("server received init packet from client\n");

				sendActionPackets();

				break;

			case ACTION_EVENT:

				// "Process" information: display the test value
				std::cout << "server received action packet from client: " << iter->first << " value: " << std::endl;

				sendActionPackets();

				break;

			default:

				printf("error in packet types\n");

				break;
			}
		}
	}
}


void ServerGame::sendActionPackets()
{
	// Send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = ACTION_EVENT;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}

void ServerGame::threadedClient(int clientId)
{
	char network_data[MAX_PACKET_SIZE];
	Packet packet;

	while (network->sessions.find(clientId) != network->sessions.end()){
		int data_length = network->receiveData(clientId, network_data);

		if (data_length <= 0)
		{
			//no data recieved
			continue;
		}

		int i = 0;
		while ((i < (unsigned int)data_length) && (network->sessions.find(clientId) != network->sessions.end()))
		{
			packet.deserialize(&(network_data[i]));
			i += packet.packet_size;

			switch (packet.packet_type) {

			case INIT_CONNECTION:

				printf("server received init packet from client\n");

				//sendActionPackets();

				break;

			case ACTION_EVENT:

				// "Process" information: display the test value
				std::cout << "server received action packet from client: " << clientId << " value: " << std::endl;

				//sendActionPackets();

				break;

			default:

				printf("error in packet types\n");

				break;
			}
		}
	}

}
