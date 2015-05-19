// Client: ClientGame.cpp
//

#include "ClientGame.h"
#include "PacketData.h"


ClientNetwork* ClientGame::network;
char ClientGame::network_data[];
GameScene * ClientGame::game;
std::thread * ClientGame::myThread;


using namespace GLNetwork;

void ClientGame::Init()
{
	network = new ClientNetwork();

	char *packet_data;

	Packet *packet = new Packet();

	const unsigned int packet_size = PacketBuilder::SerializePacket(INIT_CONNECTION, packet, packet_data);
	//packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);

	//myThread = new std::thread(update, 2);
}

void ClientGame::sendActionPackets(int i)
{
	// send action packet
	char *packet_data;

	PlayerPacket packet;
	
	//packet.forward = true;
	packet.isShooting = true;

	const unsigned int packet_size = PacketBuilder::SerializePacket(PLAYER_PACKET, &packet, packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}


void ClientGame::SendPacket(GLNetwork::PacketType packet_t, GLNetwork::Packet *packet)
{
	// send action packet
	char *packet_data;

	const unsigned int packet_size = PacketBuilder::SerializePacket(packet_t, packet, packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientGame::update(int j)
{

	while (true){
		Packet *packet;
		PlayerInfoPacket newPacket;
		int data_length = network->receivePackets(network_data);
		int packetSize = 0;
		if (data_length <= 0)
		{
			//no data recieved
			continue;
		}

		int i = 0;
		for (int i = 0; i < (unsigned int)data_length; i += packetSize)
		{

			packetSize = PacketReader::DeSerializePacket(packet, network_data, i);

			switch (network_data[i]) {

			case ACTION_EVENT:

				printf("client received action event packet from server\n");
				break;

			case PLAYER_INFO_PACKET:
			{

				printf("\nPlayer Info, objID: %d, ammo: %d, health: %d, score: %d", ((PlayerInfoPacket *)packet)->objectId, ((PlayerInfoPacket *)packet)->ammo, ((PlayerInfoPacket *)packet)->health, ((PlayerInfoPacket *)packet)->score);

				int* pInfo = PacketData::extractPlayerInfo((PlayerInfoPacket *)packet);
				printf("\nPlayer Info, objID: %d, ammo: %d, health: %d, score: %d", pInfo[0], pInfo[1], pInfo[2], pInfo[3]);

				game->UpdatePlayerInfo(pInfo[0], pInfo[1], pInfo[2], pInfo[3]);

				//sendActionPackets(j);

				break;
			}



			case PLAYER_OBJECT:{
				std::pair<glm::mat4, glm::vec3> packet_data = PacketData::packetToTransformValues((ObjectPacket *)packet);

				game->UpdateTransformObj(((ObjectPacket *)(packet))->objectId, GameScene::BoxMan, packet_data.first, packet_data.second);

				ObjectPacket *objPacket = (ObjectPacket *)packet;

				//printf("\nPlayerObjectPacket, objID: %d, pos: x: %f, y: %f, z: %f", objPacket->objectId, objPacket->posX, objPacket->posY, objPacket->posZ);

				break;

			}


			case PROJECTILE_OBJECT:{
				std::pair<glm::mat4, glm::vec3> packet_data = PacketData::packetToTransformValues((ObjectPacket *)packet);

				game->UpdateTransformObj(((ObjectPacket *)(packet))->objectId, GameScene::Spear, packet_data.first, packet_data.second);

				break;

			}

			case WALL_OBJECT:{
				std::pair<glm::mat4, glm::vec3> packet_data = PacketData::packetToTransformValues((ObjectPacket *)packet);

				game->UpdateTransformObj(((ObjectPacket *)(packet))->objectId, GameScene::Wall, packet_data.first, packet_data.second);
				break;

			}

			case FLOOR_OBJECT:{
				std::pair<glm::mat4, glm::vec3> packet_data = PacketData::packetToTransformValues((ObjectPacket *)packet);

				game->UpdateTransformObj(((ObjectPacket *)(packet))->objectId, GameScene::Floor, packet_data.first, packet_data.second);
				break;

			}

			case KILL_OBJECT:{
				game->RemoveMember((game->objIdStrId)[((ObjectPacket *)(packet))->objectId]);
				break;
			}
			default:

				printf("\nerror in packet types. PacketType: %d", network_data[i]);

				break;
			}
		}
	}


}

void ClientGame::Update(float timedelta){
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
	for (int i = 0; i < (unsigned int)data_length; i += packetSize)
	{

		packetSize = PacketReader::DeSerializePacket(packet, network_data, i);

		switch (network_data[i]) {

		case ACTION_EVENT:

			printf("client received action event packet from server\n");
			break;

		case PLAYER_INFO_PACKET:
		{

			printf("\nPlayer Info, objID: %d, ammo: %d, health: %d, score: %d", ((PlayerInfoPacket *)packet)->objectId, ((PlayerInfoPacket *)packet)->ammo, ((PlayerInfoPacket *)packet)->health, ((PlayerInfoPacket *)packet)->score);

			int* pInfo = PacketData::extractPlayerInfo((PlayerInfoPacket *)packet);
			printf("\nPlayer Info, objID: %d, ammo: %d, health: %d, score: %d", pInfo[0], pInfo[1], pInfo[2], pInfo[3]);

			game->UpdatePlayerInfo(pInfo[0], pInfo[1], pInfo[2], pInfo[3]);

			//sendActionPackets(j);

			break;
		}



		case PLAYER_OBJECT:{
			std::pair<glm::mat4, glm::vec3> packet_data = PacketData::packetToTransformValues((ObjectPacket *)packet);

			game->UpdateTransformObj(((ObjectPacket *)(packet))->objectId, GameScene::BoxMan, packet_data.first, packet_data.second);

			ObjectPacket *objPacket = (ObjectPacket *)packet;

			//printf("\nPlayerObjectPacket, objID: %d, pos: x: %f, y: %f, z: %f", objPacket->objectId, objPacket->posX, objPacket->posY, objPacket->posZ);

			break;

		}


		case PROJECTILE_OBJECT:{
			std::pair<glm::mat4, glm::vec3> packet_data = PacketData::packetToTransformValues((ObjectPacket *)packet);

			game->UpdateTransformObj(((ObjectPacket *)(packet))->objectId, GameScene::Spear, packet_data.first, packet_data.second);

			break;

		}

		case WALL_OBJECT:{
			std::pair<glm::mat4, glm::vec3> packet_data = PacketData::packetToTransformValues((ObjectPacket *)packet);

			game->UpdateTransformObj(((ObjectPacket *)(packet))->objectId, GameScene::Wall, packet_data.first, packet_data.second);
			break;

		}

		case FLOOR_OBJECT:{
			std::pair<glm::mat4, glm::vec3> packet_data = PacketData::packetToTransformValues((ObjectPacket *)packet);

			game->UpdateTransformObj(((ObjectPacket *)(packet))->objectId, GameScene::Floor, packet_data.first, packet_data.second);
			break;

		}
		case KILL_OBJECT:{
			game->RemoveMember((game->objIdStrId)[((ObjectPacket *)(packet))->objectId]);
			break;
		}
		default:

			printf("\nerror in packet types. PacketType: %d", network_data[i]);

			break;
		}
	}
}

void ClientGame::Game(GameScene *newGame)
{
	game = newGame;
}

GameScene * ClientGame::Game(void)
{
	return game;
}


