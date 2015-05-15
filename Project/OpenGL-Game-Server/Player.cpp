#include "Player.h"
#include "GroupObject.h"
#include "MeshObject.h"

Player::Player(void)
{
	GroupObject *group = new GroupObject();



	AddStat(CharacterStat("Health", 3, 0, 3));
	AddStat(CharacterStat("Ammo", 3, 0, 3));

}


Player::~Player(void)
{
	
}

MeshObject * Player::GetCollisionMesh(void)
{
	return (MeshObject *)(dynamic_cast<GameObjectContainer *>(body)->GetMember("Idle"));
}
