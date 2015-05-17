#include "PacketData.h"
#include "GLNetwork.h"


using namespace GLNetwork;


GLNetwork::ObjectPacket PacketData::transformToPacket(Transform* pTrans)
{
	ObjectPacket packet;
	glm::mat4 rot = pTrans->NetRotation();
	glm::vec3 pos = pTrans->Position();

	packet.objectId = pTrans->ObjectId();

	packet.netRot00 = rot[0][0];
	packet.netRot01 = rot[0][1];
	packet.netRot02 = rot[0][2];
	packet.netRot10 = rot[1][0];
	packet.netRot11 = rot[1][1];
	packet.netRot12 = rot[1][2];
	packet.netRot20 = rot[2][0];
	packet.netRot21 = rot[2][1];
	packet.netRot22 = rot[2][2];

	packet.posX = pos.x;
	packet.posY = pos.y;
	packet.posZ = pos.z;

	return packet;
}
GLNetwork::ObjectPacket PacketData::rigidBodyToPacket(RigidBody* pRBody)
{
	return transformToPacket(pRBody->pTrans);
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
int* PacketData::extractPlayerInfo(GLNetwork::PlayerInfoPacket* packet)
{
	int* packetInfo = new int(3);

	packetInfo[0] = packet->health;
	packetInfo[1] = packet->score;
	packetInfo[2] = packet->ammo;

	return packetInfo;
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