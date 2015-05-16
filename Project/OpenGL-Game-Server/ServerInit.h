#ifndef SERVERINIT_H
#define SERVERINIT_H

#include "BoundingBox.h"
#include "MeshObject.h"
#include "Transform.h"
#include "RigidBody.h"

#include "../Network/GLNetwork.h"

class ServerInit
{
public:
	ServerInit();
	void init();
	void initBoundingBoxes();

	GLNetwork::ObjectPacket transformToPacket(Transform* pTrans);
	GLNetwork::ObjectPacket rigidBodyToPacket(RigidBody* pRBody);

	std::pair<glm::mat4,glm::vec3> packetToTransformValues(GLNetwork::ObjectPacket* packet);/*
	extracts and returns std::pair< mat4, vec3 >
	first = Rotation
	second = Position
	*/

	int* extractPlayerInfo(GLNetwork::PlayerInfo* packet);/*
	extracts and returns int*
	int[0] = health; 
	int[1] = score; 
	int[2] = ammo; 
	*/

	std::pair<glm::mat4, bool*> extractPlayerInfo(GLNetwork::PlayerPacket* packet);/*
	extracts and returns pair< Rotation, bool*> 
	first	  = Rotation;//glm::mat4 
	second[0] = isShooting;
	second[1] = forward;
	second[2] = backward;
	second[3] = left;
	second[4] = right;
	*/

	BoundingBox* playerBox;
	BoundingBox* wallCubeBox;
	BoundingBox* spearBox;

};

#endif