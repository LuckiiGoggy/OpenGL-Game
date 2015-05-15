#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

#include "GlutManager.h"
#include "GameScene.h"

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	GlutManager::Init(false);
	InputManager::Init();	

	
	GameScene *gS = new GameScene();
	gS->Init();
	GlutManager::AddMember("Derp", gS);

	GlutManager::StartLoop();

	return 0;
}
