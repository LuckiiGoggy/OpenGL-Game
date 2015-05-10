#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

#include "WorldEngine.h"
#include "InputManager.h"
#include "IGameObject.h"
#include "GroupObject.h"
#include "TestObject.h"
#include "MeshObject.h"
#include "GLUIManager.h"
#include "GlutManager.h"
#include "GameScene.h"
#include "Player.h"

WorldEngine engine = WorldEngine();
void updateGame();
void menuEvents(int choice);
void renderScene(void);

GroupObject test;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	GlutManager::Init(false);
	InputManager::Init();	

	
	GameScene *gS = new GameScene();

	gS->Init();

	
	Player *player = new Player();
	gS->AddMember("Player", player);

	GlutManager::AddMember("Derp", gS);

	



	GlutManager::StartLoop();

	return 0;
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);

	if (engine.loaded == true) {
		engine.renderWorld();
	}


	glutSwapBuffers();
}
