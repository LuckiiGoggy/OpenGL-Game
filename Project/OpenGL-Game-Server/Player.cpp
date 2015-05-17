#include "Player.h"
#include "GroupObject.h"
#include "MeshObject.h"
#include "ServerMain.h"
#include "BoundingBoxLibrary.h"
#include "Projectile.h"

Player::Player(void)
{
	AddStat(CharacterStat("Score", 0, 0));
	AddStat(CharacterStat("Health", 3, 0, 3));
	AddStat(CharacterStat("Ammo", 3, 0, 3));

	name = "BoxMan";
	ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewPlayer(), this, name);
}

Player::Player(std::string _name)
{
	AddStat(CharacterStat("Score", 0, 0));
	AddStat(CharacterStat("Health", 3, 0, 3));
	AddStat(CharacterStat("Ammo", 3, 0, 3));
	name = _name;

	ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewPlayer(), this, name);
}


Player::~Player(void)
{
	
}

void Player::Shoot(void)
{
	Projectile *newProj;
	newProj = new Projectile(NetRotation(), Position());
	glm::vec3 vdir = Transform::ApplyTransVec3(glm::vec3(0.0f, 0.0f, -1.0f), netRotation);
	Velocity* vel = new Velocity(vdir.x * 10, vdir.y * 10, vdir.z * 10, 1, 10);
	std::string projName = name + "-projectile-" + std::to_string(GetStatValue("Ammo"));
	ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewProjectile(), newProj, name);
	ServerMain::GetPhysEngi()->addVelocityTo(name, vel);
	ServerMain::AddMember(ServerMain::Projectiles, ServerMain::GetNewObjectId(), newProj);
}

