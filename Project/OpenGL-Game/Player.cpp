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
	chara = new Character();
	controller = new CharacterController(chara);


//	camera->Move(glm::vec3(0.0f, 3.0f, 10.0f));
	//camera->SetCameraLookAt(glm::vec3(-0.0f, -2.0f, 8.0f));

	group->AddMember("Mesh", boxman);

	group->AddMember("Camera", camera);

	

	chara->AddMember("Sonic", group);

	GlutManager::SetMainCamera(camera);
}


Player::~Player(void)
{
	if(chara)		delete chara;
	if(controller)  delete controller;
}

void Player::Update(float timeDelta){
	
	if (InputManager::isSpecialKeyDown(GLUT_KEY_LEFT))  chara->RotateY(1.0f  * timeDelta);
	if (InputManager::isSpecialKeyDown(GLUT_KEY_RIGHT)) chara->RotateY(-1.0f * timeDelta);
	if (InputManager::isSpecialKeyDown(GLUT_KEY_UP))
	{
		chara->RotateX(1.0f  * timeDelta);
		delta++;
	}
	if (InputManager::isSpecialKeyDown(GLUT_KEY_DOWN))	chara->RotateX(-1.0f * timeDelta);
	if (InputManager::isKeyDown(','))					chara->RotateZ(0.1f  * timeDelta);
	if (InputManager::isKeyDown('.'))					chara->RotateZ(-0.1f * timeDelta);


	controller->Update(timeDelta);
	chara->Update(timeDelta);
}

void Player::Render(void){
	chara->Render();
}