#include "Player.h"
#include "GroupObject.h"
#include "Camera.h"
#include "MeshObject.h"
#include "GlutManager.h"
#include "AnimatedObject.h"
#include "GameObjectLibrary.h"

Player::Player(void)
{
	GroupObject *group = new GroupObject();
	Camera *camera = new Camera();

	

	SetBody(GameObjectLibrary::NewPlayer());



	AddStat(CharacterStat("Health", 3, 0, 3));
	AddStat(CharacterStat("Ammo", 3, 0, 3));
	AddStat(CharacterStat("Score", 0, 0));

}


Player::~Player(void)
{
	
}

MeshObject * Player::GetCollisionMesh(void)
{
	return (MeshObject *)(dynamic_cast<GameObjectContainer *>(body)->GetMember("Idle"));
}

void Player::NetRotation(glm::mat4 &rot)
{

}
