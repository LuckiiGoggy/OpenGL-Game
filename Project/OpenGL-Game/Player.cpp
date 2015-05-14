#include "Player.h"
#include "GroupObject.h"
#include "Camera.h"
#include "MeshObject.h"
#include "GlutManager.h"
#include "AnimatedObject.h"

Player::Player(void)
{
	GroupObject *group = new GroupObject();
	Camera *camera = new Camera();

	
	SetBody(new AnimatedObject());


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
