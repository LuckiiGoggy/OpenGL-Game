#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

#include "GlutManager.h"
#include "GameScene.h"
#include "ClientGame.h"

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	GlutManager::Init(false);
	InputManager::Init();	

	ClientGame::Init();
	
	GameScene *gS = new GameScene();
	gS->Init();
	GlutManager::AddMember("Derp", gS);

	GlutManager::StartLoop();

	return 0;
}
