#include "openGL.h"
#include <iostream>
#include "GlutManager.h"
#include "InputManager.h"
#include "GLUIManager.h"

GLint GlutManager::mainWindow;
float GlutManager::lastTime;


void GlutManager::Init(bool editor)
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);//optional
	glutInitWindowSize(566, 400); //optional

	mainWindow = glutCreateWindow("World Editor");

	glewInit();
	if (glewIsSupported("GL_VERSION_4_0")) {
		std::cout << "GLEW Version is 4.0\n";
	}
	else {
		std::cout << "GLEW 4.0 not supported\n";
	}

	//glEnable(GL_DEPTH_TEST);	
	//glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(GlutManager::RenderScene);
	glutIdleFunc(GlutManager::IdleFunc);
	//glutReshapeFunc(GlutManager::Reshape);

	InputManager::Init();

	lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	if (editor)	GLUIManager::initGLUI(GlutManager::mainWindow, GlutManager::IdleFunc);
	else glutFullScreen();
}


GlutManager::~GlutManager()
{
}

void GlutManager::StartLoop(void){
	glutMainLoop();
}

void GlutManager::EndLoop(void){
	/**Clean Up**/
	glutLeaveMainLoop();
}

void GlutManager::RenderScene(void){

	//std::cout << "\n In RenderScene";


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);


	if (GLUIManager::engine.loaded == true) {
		GLUIManager::engine.renderWorld();
	}


	glutSwapBuffers();
}

void GlutManager::IdleFunc(void){

	float currTime = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

	float currDelta = currTime - lastTime;
	lastTime = currTime;
	if (InputManager::isKeyDown(KeyCodes::ESC)) glutLeaveMainLoop();

	if (InputManager::isLeftButtonDown() && GLUIManager::engine.loaded == true) {
		Point p = InputManager::GetMousePos();
		GLUIManager::engine.updateSquare(p, GLUIManager::radiogroup->get_int_val());
	}
	
	float moveSpd = currDelta * 1.0f;

	glutSetWindow(mainWindow);

	glutPostRedisplay();
}

void GlutManager::Reshape(int x, int y) {
	/*
	GLUI_Master.auto_set_viewport();
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glutSetWindow(mainWindow);
	glutPostRedisplay();
}
