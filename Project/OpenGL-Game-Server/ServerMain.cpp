#include "openGL.h"
#include "ServerMain.h"
#include "PacketData.h"
#include "BoundingBoxLibrary.h"


GameObjectContainer ServerMain::players;
GameObjectContainer ServerMain::floors;
GameObjectContainer ServerMain::walls;
GameObjectContainer ServerMain::projectiles;
PhysicsEngine * ServerMain::physEngi;
ServerGame * ServerMain::server;

bool ServerMain::isRunning = false;
float ServerMain::currDelta;
float ServerMain::lastTime;
int ServerMain::lastObjectId;



void ServerMain::SetPhysEngi(PhysicsEngine * newPhysEngi)
{
	physEngi = newPhysEngi;
}

PhysicsEngine * ServerMain::GetPhysEngi(void)
{
	return physEngi;
}

void ServerMain::Init(void)
{
	physEngi = new PhysicsEngine();
	server = new ServerGame();
	lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	isRunning = true;
	lastObjectId = 0;
	
	BoundingBoxLibrary::InitBoxes();
	//ServerInit::init();
}

void ServerMain::StartLoop()
{
	while (isRunning){
		server->update();
		float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

		currDelta = currTime - lastTime;
		lastTime = currTime;

		//Loop
		physEngi->ApplyVelocities(currDelta);
		physEngi->bruteCollision();
		physEngi->updateVelocities();
		physEngi->ApplyVelocities(currDelta);
		physEngi->updateVelocities();

		players.UpdateMembers(currDelta);
		walls.UpdateMembers(currDelta);
		floors.UpdateMembers(currDelta);
 		projectiles.UpdateMembers(currDelta);

		//Loop
			//go through members and get pos and rotation
			//stuff into packets
		SendMemberPackets(GLNetwork::PLAYER_OBJECT, players);
		SendMemberPackets(GLNetwork::FLOOR_OBJECT, floors);
		SendMemberPackets(GLNetwork::WALL_OBJECT, walls);
		SendMemberPackets(GLNetwork::PROJECTILE_OBJECT, projectiles);
		//Send Packets


	}

}

void ServerMain::EndLoop()
{
	isRunning = false;
}

void ServerMain::AddMember(MemberList listType, int objectId, IGameObject *object)
{
	switch (listType)
	{
	case Players:
		players.AddMember(objectId, object);
		break;
	case Walls:
		walls.AddMember(objectId, object);
		break;
	case Floors:
		floors.AddMember(objectId, object);
		break;
	case Projectiles:
		projectiles.AddMember(objectId, object);
		break;
	}

}

IGameObject *ServerMain::GetMember(MemberList listType, int objectId)
{
	switch (listType)
	{
	case Players:
		return players.GetMember(objectId);
		break;
	case Walls:
		return walls.GetMember(objectId);
		break;
	case Floors:
		return floors.GetMember(objectId);
		break;
	case Projectiles:
		return projectiles.GetMember(objectId);
		break;
	}

	return NULL;
}

int ServerMain::GetNewObjectId(void)
{
	return lastObjectId++;
}

void ServerMain::SendMemberPackets(GLNetwork::PacketType packet_t, GameObjectContainer members)
{
	std::map<int, IGameObject *>::iterator iter;
	Transform *transformable;

	for (iter = members.members.begin(); iter != members.members.end(); ++iter) {
		transformable = dynamic_cast<Transform*>(iter->second);
		if (transformable != 0){
			ServerGame::SendToAll(packet_t, &(transformable->GetPacket()));
		}
	}
}

