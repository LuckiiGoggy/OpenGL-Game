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
WorldEngine * ServerMain::engine;
Spawner * ServerMain::spawner;

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
	
	engine = new WorldEngine();
	engine->readWorld("level");

	spawner = new Spawner(engine->squares);
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

		std::map<int, IGameObject *>::iterator iter = projectiles.members.begin();;
		Projectile *projectile;

		while (iter != projectiles.members.end()) 
		{
			projectile = dynamic_cast<Projectile*>(iter->second);
			
			if (projectile != 0){
				if (!projectile->IsActive()){
					iter = ServerMain::RemoveMember(ServerMain::Projectiles, projectile->ObjectId(), iter);
				}
				else{
					++iter;
				}
			}
			else{
				++iter;
			}

		}




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
		spawner->SpawnPlayer((Player *)object, players.GetMembers());
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

void ServerMain::RemoveMember(MemberList listType, int objectId)
{
	GLNetwork::KillObjectPacket killPacket;
	killPacket.objectId = objectId;

	switch (listType)
	{
	case Players:
		players.RemoveMember(objectId);
		physEngi->unregisterRigidBody("Player" + std::to_string(objectId));
		break;
	case Walls:
		walls.RemoveMember(objectId);
		physEngi->unregisterRigidBody("Wall" + std::to_string(objectId));
		break;
	case Floors:
		floors.RemoveMember(objectId);
		break;
	case Projectiles:
		projectiles.RemoveMember(objectId);
		physEngi->unregisterRigidBody("Projectile" + std::to_string(objectId));
		break;
	}
	ServerGame::SendToAll(GLNetwork::KILL_OBJECT, &killPacket);
}

std::map<int, IGameObject*>::iterator ServerMain::RemoveMember(MemberList listType, int objectId, std::map<int, IGameObject*>::iterator it)
{
	GLNetwork::KillObjectPacket killPacket;
	killPacket.objectId = objectId;
	ServerGame::SendToAll(GLNetwork::KILL_OBJECT, &killPacket);

	switch (listType)
	{
	case Players:
		physEngi->unregisterRigidBody("Player" + std::to_string(objectId));
		return players.RemoveMember(it);
		break;
	case Walls:
		physEngi->unregisterRigidBody("Wall" + std::to_string(objectId));
		return walls.RemoveMember(it);
		break;
	case Floors:
		return floors.RemoveMember(it);
		break;
	case Projectiles:
		physEngi->unregisterRigidBody("Projectile" + std::to_string(objectId));
		return projectiles.RemoveMember(it);
		break;
	}

	return it;
}

