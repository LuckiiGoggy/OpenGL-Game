#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

#define DEBUG

//Santo Tallarico COMP4900 World Builder/Editor
#include "WorldEngine.h"
#include "InputManager.h"
#include "IGameObject.h"
#include "GroupObject.h"
#include "TestObject.h"
#include "MeshObject.h"

const int SAVE = 1;
const int LOAD = 2;
WorldEngine engine;
void updateGame();
void menuEvents(int choice);
void renderScene(void);
MeshObject myMesh;





GroupObject testGroup;

int main(int argc, char **argv) {
	int menu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);//optional
	glutInitWindowSize(400, 400); //optional

	glutCreateWindow("OpenGL First Window");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return 1;
	}
	if (glewIsSupported("GL_VERSION_4_0")) {
		std::cout << "GLEW Version is 4.0\n";
	}
	else {
		std::cout << "GLEW 4.0 not supported\n";
	}

	char* obj_filename = (char*) "../Assets/Models/suzanne.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	myMesh.Init(obj_filename, v_shader_filename, f_shader_filename);

	glutDisplayFunc(renderScene);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glDepthRange(1, 0);

	glutKeyboardFunc(InputManager::KeyPress);
	glutKeyboardUpFunc(InputManager::KeyUp);
	glutSpecialFunc(InputManager::SpecialKeyPress);
	glutSpecialUpFunc(InputManager::SpecialKeyUp);

	glutMouseFunc(InputManager::MouseInput);
	InputManager::Init();

	//glutDisplayFunc(renderScene);

	glutIdleFunc(updateGame);

	menu = glutCreateMenu(menuEvents);
	glutAddMenuEntry("Save", SAVE);
	glutAddMenuEntry("Load", LOAD);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	testGroup.AddMember("TestObject", new TestObject);

	glutFullScreen();

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
	glClearColor(0.5, 0.5, 0.5, 1.0);

	myMesh.Update(0.0f);
	myMesh.draw();
	myMesh.draw_bbox();

	if (engine.loaded == true) {
		engine.renderWorld();
	}


	glutSwapBuffers();
}

