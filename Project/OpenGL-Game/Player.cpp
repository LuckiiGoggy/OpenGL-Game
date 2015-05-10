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

	

	chara->AddMember("BoxMan", group);

	GlutManager::SetMainCamera(camera);

	chara->AddStat(CharacterStat("Health", 3, 0, 3));
	chara->AddStat(CharacterStat("Ammo", 3, 0, 3));

	lastMouseX = lastMouseY = -1;
}


Player::~Player(void)
{
	if(chara)		delete chara;
	if(controller)  delete controller;
}

void Player::Update(float timeDelta){
	int currMouseXDelta = 0;
	int currMouseYDelta = 0;

	if (lastMouseX != -1 && lastMouseY != -1){
		currMouseXDelta = InputManager::GetMousePos().x - lastMouseX;
		currMouseYDelta = InputManager::GetMousePos().y - lastMouseY;
	}

	lastMouseX = InputManager::GetMousePos().x;
	lastMouseY = InputManager::GetMousePos().y;

	chara->RotateY((float)currMouseXDelta * timeDelta);


	controller->Update(timeDelta);
	chara->Update(timeDelta);
}

void Player::Render(void){
	chara->Render();
}

glm::vec3 Player::Position(void)
{
	GroupObject * group = dynamic_cast<GroupObject *>(chara->GetMember("BoxMan"));
	
	if (group != 0) return group->Position();

	return glm::vec3(0.0f);
}

Character * Player::Chara(void)
{
	return chara;
}
