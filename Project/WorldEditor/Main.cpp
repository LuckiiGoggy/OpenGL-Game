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
	glutInit(&argc, argv);
	GlutManager::Init(true);
	
	InputManager::Init();
	
	GlutManager::StartLoop();

	return 0;
}