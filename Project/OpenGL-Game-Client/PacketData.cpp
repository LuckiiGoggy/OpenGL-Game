#include "PacketData.h"
#include "GLNetwork.h"


using namespace GLNetwork;


int* PacketData::extractPlayerInfo(GLNetwork::PlayerInfoPacket* packet)
{
	int* packetInfo = new int(4);

	packetInfo[0] = packet->objectId;

	packetInfo[1] = packet->health;
	packetInfo[2] = packet->ammo;
	packetInfo[3] = packet->score;

	return packetInfo;
}

std::pair<glm::mat4, glm::vec3> PacketData::packetToTransformValues(GLNetwork::ObjectPacket* packet)
{
	glm::mat4 rot = glm::mat4(1.0);
	glm::vec3 pos = glm::vec3(0.0);

	rot[0][0] = packet->netRot00;
	rot[0][1] = packet->netRot01;
	rot[0][2] = packet->netRot02;
	rot[1][0] = packet->netRot10;
	rot[1][1] = packet->netRot11;
	rot[1][2] = packet->netRot12;
	rot[2][0] = packet->netRot20;
	rot[2][1] = packet->netRot21;
	rot[2][2] = packet->netRot22;

	pos.x = packet->posX;
	pos.y = packet->posY;
	pos.z = packet->posZ;

	return std::pair<glm::mat4, glm::vec3>(rot, pos);
}


std::pair<glm::mat4, bool*> PacketData::extractPlayerInfo(GLNetwork::PlayerPacket* packet)
{
	glm::mat4 rot = glm::mat4(1.0);

	rot[0][0] = packet->netRot00;
	rot[0][1] = packet->netRot01;
	rot[0][2] = packet->netRot02;
	rot[1][0] = packet->netRot10;
	rot[1][1] = packet->netRot11;
	rot[1][2] = packet->netRot12;
	rot[2][0] = packet->netRot20;
	rot[2][1] = packet->netRot21;
	rot[2][2] = packet->netRot22;

	bool *packetInfo = new bool[5];
	packetInfo[0] = packet->isShooting;
	packetInfo[1] = packet->forward;
	packetInfo[2] = packet->backward;
	packetInfo[3] = packet->left;
	packetInfo[4] = packet->right;


	return std::pair<glm::mat4, bool*>(rot, packetInfo);
}