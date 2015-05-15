#include "ServerMain.h"


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
}

std::map<std::string, IObject *> ServerMain::members;

PhysicsEngine * ServerMain::physEngi;
