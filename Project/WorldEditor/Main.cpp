#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

#include "WorldEngine.h"
#include "InputManager.h"
#include "GLUIManager.h"
#include "GlutManager.h"

WorldEngine engine = WorldEngine();
void updateGame();
void menuEvents(int choice);
void renderScene(void);

int main(int argc, char **argv) {
	int menu;
	glutInit(&argc, argv);
	GlutManager::Init(true);
	
	InputManager::Init();
	
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
