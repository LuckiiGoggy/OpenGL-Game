// Server: ServerGame.cpp
//

#include "ServerGame.h"
#include "ServerMain.h"
#include "Player.h"

unsigned int ServerGame::client_id = 0;
ServerNetwork* ServerGame::network = new ServerNetwork();
std::map<unsigned int, int> ServerGame::clients;


using namespace GLNetwork;

ServerGame::ServerGame(void)
{
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

		int newObjId = ServerMain::GetNewObjectId();

		clients[client_id] = newObjId;
		Player *player = new Player();

		ServerMain::AddMember(newObjId, player);

		PlayerInfoPacket playerInfo;
		playerInfo.ammo = player->GetStatValue("Ammo");
		playerInfo.health = player->GetStatValue("Health");
		playerInfo.score = player->GetStatValue("Score");

		SendPacketToClient(&playerInfo, client_id);

		client_id++;

	}

	//receiveFromClients();
	//sendActionPackets();
}



void ServerGame::sendActionPackets()
{
	Packet *packet = new PlayerInfoPacket();
	// Send action packet
	unsigned int packet_size;
	char *packet_data;


	
	packet_size = PacketBuilder::SerializePacket(PLAYER_INFO_PACKET, packet, packet_data);
	//packet->serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}

void ServerGame::threadedClient(int clientId)
{
	char network_data[MAX_PACKET_SIZE];
	Packet *packet;

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
			int packetSize = PacketReader::DeSerializePacket(packet, network_data, i);

			//packet.deserialize(&(network_data[i]));
			i += packetSize;

			switch (network_data[i]) {

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

void ServerGame::RemoveClient(unsigned int clientId)
{
	if (clients.find(clientId) != clients.end()){
		clients.erase(clientId);
	}
}

void ServerGame::sendPackets(GLNetwork::Packet *packet)
{
	unsigned int packet_size;
	char *packet_data;

	packet_size = PacketBuilder::SerializePacket(ACTION_EVENT, packet, packet_data);
	//packet->serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}

void ServerGame::SendPacketToClient(GLNetwork::Packet *packet, unsigned int clientId)
{
	unsigned int packet_size;
	char *packet_data;

	packet_size = PacketBuilder::SerializePacket(packet->PacketType(), packet, packet_data);

	network->SendToOne(clientId, packet_data, packet_size);
}
