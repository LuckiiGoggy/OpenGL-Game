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
	AnimatedObject *boxman = new AnimatedObject();


	GlutManager::GetPhysEngi()->registerRigidBody((MeshObject *)boxman->GetMember("Idle"), this, "BoxMan");
	

	GroupObject::AddMember("BoxMan", boxman);


	AddStat(CharacterStat("Health", 3, 0, 3));
	AddStat(CharacterStat("Ammo", 3, 0, 3));

}


Player::~Player(void)
{
}
