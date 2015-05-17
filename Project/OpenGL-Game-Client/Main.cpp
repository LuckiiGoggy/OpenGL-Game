#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

#include "GlutManager.h"
#include "GameScene.h"
#include "ClientGame.h"
#include "GameObjectLibrary.h"

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	GlutManager::Init(false);
	InputManager::Init();	
	GameObjectLibrary::InitGameObjects();
	GameScene *gS = new GameScene();
	gS->Init();
	ClientGame::Init();
	ClientGame::Game(gS);
	GlutManager::AddMember("Derp", gS);

	GlutManager::StartLoop();

	return 0;
}
