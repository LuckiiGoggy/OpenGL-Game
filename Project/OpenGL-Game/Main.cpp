#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

//Santo Tallarico COMP4900 World Builder/Editor
#include "WorldEngine.h"
#include "InputManager.h"

const int SAVE = 1;
const int LOAD = 2;
WorldEngine engine;
void updateGame();
void menuEvents(int choice);
void renderScene(void);

int main(int argc, char **argv) {
	int menu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);//optional
	glutInitWindowSize(400, 400); //optional

	glutCreateWindow("OpenGL First Window");

	glewInit();
	if (glewIsSupported("GL_VERSION_4_0")) {
		std::cout << "GLEW Version is 4.0\n";
	}
	else {
		std::cout << "GLEW 4.0 not supported\n";
	}

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(renderScene);
	
	glutKeyboardFunc(InputManager::KeyPress);
	glutKeyboardUpFunc(InputManager::KeyUp);
	glutSpecialFunc(InputManager::SpecialKeyPress);
	glutSpecialUpFunc(InputManager::SpecialKeyUp);

	glutMouseFunc(InputManager::MouseInput);

	glutMotionFunc(InputManager::MouseMotion);
	glutPassiveMotionFunc(InputManager::MouseMotion);

	glutIdleFunc(updateGame);

	menu = glutCreateMenu(menuEvents);
	glutAddMenuEntry("Save", SAVE);
	glutAddMenuEntry("Load", LOAD);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

	return 0;
}


void updateGame()
{
	if (InputManager::isKeyDown(KeyCodes::ESC)) glutLeaveMainLoop();
		glutPostRedisplay();
}

void menuEvents(int choice) {
	switch (choice) {
	case SAVE: {
		if (engine.loaded = false) {
			engine.writeWorld();
		}
		break;
	}
	case LOAD: {
		engine.readWorld();
		break;
	}
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	if (engine.loaded == true) {
		engine.renderWorld();
	}

	glutSwapBuffers();
}

