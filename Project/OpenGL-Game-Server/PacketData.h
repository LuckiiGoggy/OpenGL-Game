#ifndef PACKETDATA_H
#define PACKETDATA_H

#include "Transform.h"
#include "RigidBody.h"

#include "GLNetwork.h"

class PacketData
{
public:
	static GLNetwork::ObjectPacket transformToPacket(Transform* pTrans);
	static GLNetwork::ObjectPacket rigidBodyToPacket(RigidBody* pRBody);

	static std::pair<glm::mat4,glm::vec3> packetToTransformValues(GLNetwork::ObjectPacket* packet);/*
	extracts and returns std::pair< mat4, vec3 >
	first = Rotation
	second = Position
	*/

	static int* extractPlayerInfo(GLNetwork::PlayerInfoPacket* packet);/*
	extracts and returns int*
	int[0] = health; 
	int[1] = score; 
	int[2] = ammo; 
	*/

	static std::pair<glm::mat4, bool*> extractPlayerInfo(GLNetwork::PlayerPacket* packet);/*
	extracts and returns pair< Rotation, bool*> 
	first	  = Rotation;//glm::mat4 
	second[0] = isShooting;
	second[1] = forward;
	second[2] = backward;
	second[3] = left;
	second[4] = right;
	*/

};

#endif