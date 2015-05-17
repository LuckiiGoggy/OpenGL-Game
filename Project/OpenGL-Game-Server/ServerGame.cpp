// Server: ServerGame.cpp
//

#include "ServerGame.h"
#include "ServerMain.h"
#include "Player.h"
#include "PacketData.h"

unsigned int ServerGame::client_id = 0;
ServerNetwork* ServerGame::network = new ServerNetwork();
std::map<unsigned int, int> ServerGame::clients;
std::vector<std::thread *> ServerGame::myThreads;
char ServerGame::network_data[];


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

		int newObjId = ServerMain::GetNewObjectId();

		clients[client_id] = newObjId;
		Player *player = new Player("Player" + std::to_string(newObjId));

		ServerMain::AddMember(ServerMain::Players, newObjId, player);

		PlayerInfoPacket playerInfo;
		playerInfo.objectId = newObjId;
		playerInfo.ammo = player->GetStatValue("Ammo");
		playerInfo.health = player->GetStatValue("Health");
		playerInfo.score = player->GetStatValue("Score");

		SendPacketToClient(&playerInfo, client_id);

		myThreads.push_back(new std::thread(threadedClient, client_id));
		client_id++;

	}

	//receiveFromClients();
	//sendActionPackets();
}



void ServerGame::sendActionPackets()
{
	Packet *packet = new Packet();
	// Send action packet
	unsigned int packet_size;
	char *packet_data;
		
	packet_size = PacketBuilder::SerializePacket(ACTION_EVENT, packet, packet_data);
	//packet->serialize(packet_data);

	network->sendToAll(packet_data, packet_size);

	delete packet_data;
	delete packet;
}

void ServerGame::threadedClient(int clientId)
{
	int objectId = clients[clientId];
	char network_data[MAX_PACKET_SIZE]; 
	Player * player = (Player*)ServerMain::GetMember(ServerMain::Players, objectId);
	Packet *packet;

	while (network->sessions.find(clientId) != network->sessions.end()){
		int data_length = network->receiveData(clientId, network_data);

		if (data_length <= 0)
		{
			//no data received
			continue;
		}

		int i = 0;
		while ((i < (unsigned int)data_length) && (network->sessions.find(clientId) != network->sessions.end()))
		{
			int packetSize = PacketReader::DeSerializePacket(packet, network_data, i);

			//packet.deserialize(&(network_data[i]));

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

			case PLAYER_PACKET:{
				std::pair<glm::mat4, bool*> packetData = PacketData::extractPlayerInfo((PlayerPacket *)packet);
				player = (Player*)ServerMain::GetMember(ServerMain::Players, objectId);
				std::cout << "\nReceived Player Packet";

				if (player == NULL) {
					std::cout << "\n Player is NULL";
					break;
				}
				if (((PlayerPacket *)packet)->forward)
					player->MoveForward();
				if (((PlayerPacket *)packet)->backward)
					player->MoveBackward();
				if (((PlayerPacket *)packet)->left)
					player->MoveLeft();
				if (((PlayerPacket *)packet)->right)
					player->MoveRight();
				if (((PlayerPacket *)packet)->isShooting)
					player->Shoot();

				player->NetRotation(packetData.first);
				break;
			}
				


			default:

				printf("error in packet types\n");

				break;
			}

			i += packetSize;
		}


		player = (Player*)ServerMain::GetMember(ServerMain::Players, objectId);
		SendPacketToClient(GLNetwork::PLAYER_INFO_PACKET, player->GetPInfoPacket(), clientId);



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


void ServerGame::SendPacketToClient(GLNetwork::PacketType packet_t, GLNetwork::Packet *packet, unsigned int clientId)
{
	unsigned int packet_size;
	char *packet_data;

	packet_size = PacketBuilder::SerializePacket(packet_t, packet, packet_data);

	network->SendToOne(clientId, packet_data, packet_size);
}

void ServerGame::SendToAll(GLNetwork::PacketType packet_t, GLNetwork::Packet *packet)
{
	unsigned int packet_size;
	char *packet_data;

	packet_size = PacketBuilder::SerializePacket(packet_t, packet, packet_data);

	network->sendToAll(packet_data, packet_size);
}

