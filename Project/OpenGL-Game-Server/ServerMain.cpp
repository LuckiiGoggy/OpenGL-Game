#include "openGL.h"
#include "ServerMain.h"


std::map<int, Transform *> ServerMain::members;
PhysicsEngine * ServerMain::physEngi;
ServerGame * ServerMain::server;

bool ServerMain::isRunning = false;
float ServerMain::currDelta;
float ServerMain::lastTime;


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
}

void ServerMain::StartLoop()
{
	while (isRunning){
		server->update();
		float currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

		currDelta = currTime - lastTime;
		lastTime = currTime;


		//Loop
		//CheckPlayerInput
		//AddVelocity

		//Loop
// 		physEngi->ApplyVelocities(currDelta);
// 		physEngi->bruteCollision();
// 		physEngi->updateVelocities();
// 		physEngi->ApplyVelocities(currDelta);
// 		physEngi->updateVelocities();

		//Loop
			//go through members and get pos and rotation
			//stuff into packets

		//Send Packets


	}

}

void ServerMain::EndLoop()
{
	isRunning = false;
}

void ServerMain::AddMember(int objectId, Transform *object)
{
	members[objectId] = object;
}

Transform *ServerMain::GetMember(int objectId)
{
	if (members.find(objectId) != members.end()){
		return members[objectId];
	}
}

