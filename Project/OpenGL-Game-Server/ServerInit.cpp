#include "ServerInit.h"
#include "GLNetwork.h"

using namespace GLNetwork;


ServerInit::ServerInit()
{
	wallCubeBox = new BoundingBox();
	spearBox = new BoundingBox();
	playerBox = new BoundingBox();

}

void ServerInit::init()
{
	initBoundingBoxes();
}
void ServerInit::initBoundingBoxes()
{
	char* spear_obj_filename = (char*) "../Assets/Models/spear.obj";
	char* bottomFace_obj_filename = (char*) "../Assets/Models/face.obj";
	char* wallCube_obj_filename = (char*) "../Assets/Models/wallCube.obj";
	char* floorCube_obj_filename = (char*) "../Assets/Models/floorCube.obj";
	char* boxMan_obj_filename = (char*) "../Assets/Models/boxMan.obj";
	//char* sonic_obj_filename = (char*) "../Assets/Models/sonic.obj";
	char* v_shader_filename1 = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename1 = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	MeshObject spearMesh =  MeshObject();
	MeshObject boxManMesh =  MeshObject();
	MeshObject wallCubeMesh =  MeshObject();


	spearMesh.Init(spear_obj_filename, v_shader_filename1, f_shader_filename1);
	boxManMesh.Init(boxMan_obj_filename, v_shader_filename1, f_shader_filename1);
	wallCubeMesh.Init(wallCube_obj_filename, v_shader_filename1, f_shader_filename1);

	*spearBox = spearMesh.boundingBox;
	*playerBox = boxManMesh.boundingBox;
	*wallCubeBox = wallCubeMesh.boundingBox;
}

GLNetwork::ObjectPacket ServerInit::transformToPacket(Transform* pTrans)
{
	ObjectPacket packet;
	glm::mat4 rot = pTrans->NetRotation();
	glm::vec3 pos = pTrans->Position();

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
GLNetwork::ObjectPacket ServerInit::rigidBodyToPacket(RigidBody* pRBody)
{
	ObjectPacket packet;
	glm::mat4 rot = pRBody->pTrans->NetRotation();
	glm::vec3 pos = pRBody->pTrans->Position();

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
std::pair<glm::mat4, glm::vec3> ServerInit::packetToTransformValues(GLNetwork::ObjectPacket* packet)
{
	glm::mat4 rot = glm::mat4();
	glm::vec3 pos = glm::vec3();

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
int* ServerInit::extractPlayerInfo(GLNetwork::PlayerInfo* packet)
{
	int* packetInfo = new int(3);

	packetInfo[0] = packet->health;
	packetInfo[1] = packet->score;
	packetInfo[2] = packet->ammo;

	return packetInfo;
}
std::pair<glm::mat4, bool*> extractPlayerInfo(GLNetwork::PlayerPacket* packet)
{
	glm::mat4 rot = glm::mat4();

	rot[0][0] = packet->netRot00;
	rot[0][1] = packet->netRot01;
	rot[0][2] = packet->netRot02;
	rot[1][0] = packet->netRot10;
	rot[1][1] = packet->netRot11;
	rot[1][2] = packet->netRot12;
	rot[2][0] = packet->netRot20;
	rot[2][1] = packet->netRot21;
	rot[2][2] = packet->netRot22;

	bool* packetInfo = new bool(4);
	packetInfo[0] = packet->isShooting;
	packetInfo[1] = packet->forward;
	packetInfo[2] = packet->backward;
	packetInfo[3] = packet->left;
	packetInfo[4] = packet->right;


	return std::pair<glm::mat4, bool*>(rot, packetInfo);
}