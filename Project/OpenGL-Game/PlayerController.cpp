#include "PlayerController.h"
#include "Camera.h"
#include "GlutManager.h"


PlayerController::PlayerController(Player *playa) : CharacterController(playa)
{
	Camera *camera = new Camera();
	playa->GroupObject::AddMember("Camera", camera);
	GlutManager::SetMainCamera(camera);

	lastMouseX = lastMouseY = -1;
}




PlayerController::~PlayerController()
{
}

void PlayerController::Update(float timeDelta){
	CharacterController::Update(timeDelta);

	int currMouseXDelta = 0;
	int currMouseYDelta = 0;

	if (lastMouseX != -1 && lastMouseY != -1){
		currMouseXDelta = InputManager::GetMousePos().x - lastMouseX;
		currMouseYDelta = InputManager::GetMousePos().y - lastMouseY;
	}

	lastMouseX = InputManager::GetMousePos().x;
	lastMouseY = InputManager::GetMousePos().y;

	chara->RotateY((float)currMouseXDelta * timeDelta);
}