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
	ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewPlayer(), this, name, 2, 1.0f);

	ammoCD = 2.0f;
	ammoCDTimer = 0.0f;
}

Player::Player(std::string _name)
{
	AddStat(CharacterStat("Score", 0, 0));
	AddStat(CharacterStat("Health", 3, 0, 3));
	AddStat(CharacterStat("Ammo", 3, 0, 3));
	name = _name;

	ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewPlayer(), this, name, 2, 1.0f);

	ammoCD = 2.0f;
	ammoCDTimer = 0.0f;
}


Player::~Player(void)
{
	
}

void Player::Shoot(void)
{
	if (GetStatValue("Ammo") > 0){
		Projectile *newProj;
		int objId = ServerMain::GetNewObjectId();
		newProj = new Projectile(NetRotation(), Position());
		glm::vec3 vdir = Transform::ApplyTransVec3(glm::vec3(0.0f, 0.0f, -1.0f), netRotation);
		Velocity* vel = new Velocity(vdir.x * 10, vdir.y * 10, vdir.z * 10, 1, 10);
		std::string projName = "Projectile" + std::to_string(objId);
		ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewProjectile(), newProj, projName);
		ServerMain::GetPhysEngi()->addVelocityTo(projName, vel);
		ServerMain::AddMember(ServerMain::Projectiles, objId, newProj);


		if (GetStatValue("Ammo") == 3) ammoCDTimer = 0.0f;


		DecStat("Ammo");
	}
}

void Player::Update(float timeDelta)
{
	Character::Update(timeDelta);
	ammoCDTimer += timeDelta;

	if (ammoCDTimer >= ammoCD){
		IncStat("Ammo");
		ammoCDTimer = 0.0f;
	}


}

GLNetwork::Packet *Player::GetPInfoPacket(void)
{
	return &pInfoPacket;
}



void Player::IncStat(std::string statName){
	Character::IncStat(statName);
	UpdatePInfoPacket();
}
void Player::DecStat(std::string statName){
	Character::DecStat(statName);
	UpdatePInfoPacket();
}
void Player::ResetStats(void){
	Character::ResetStats();
	UpdatePInfoPacket();
}

void Player::UpdatePInfoPacket(void)
{
	pInfoPacket.objectId = objectId;
	pInfoPacket.ammo = GetStatValue("Ammo");
	pInfoPacket.health = GetStatValue("Health");
	pInfoPacket.score = GetStatValue("Score");

	ServerGame::SendPacketToClient(GLNetwork::PLAYER_INFO_PACKET, &pInfoPacket, ServerGame::clients[objectId]);
}
