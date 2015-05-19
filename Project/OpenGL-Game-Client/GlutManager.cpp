#include "openGL.h"
#include <iostream>
#include "GlutManager.h"
#include "IRenderable.h"
#include "InputManager.h"

std::map<std::string, IObject *> GlutManager::members;
Camera *GlutManager::mainCamera = NULL;
GLint GlutManager::mainWindow;
float GlutManager::lastTime;

void GlutManager::Init(bool editor)
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);//optional
	glutInitWindowSize(566, 400); //optional

	mainWindow = glutCreateWindow("OpenGL First Window");

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

	glutSetCursor(GLUT_CURSOR_NONE);

	lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;

	mainCamera = new Camera();
	//glutFullScreen();
	//if (editor)	GLUIManager::initGLUI(GlutManager::mainWindow, GlutManager::IdleFunc);
	//else glutFullScreen();



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


	
	std::map<std::string, IObject *>::iterator iter;
	IRenderable *renderable;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		renderable = dynamic_cast<IRenderable*>(iter->second);
		if (renderable != 0){
			//std::cout << "\n Rendering: " << iter->first;
			renderable->Render();
		}
	}
	
	glutSwapBuffers();
}

void GlutManager::IdleFunc(void){

	float currTime = glutGet(GLUT_ELAPSED_TIME)/1000.0f;

	currDelta = currTime - lastTime;
	lastTime = currTime;
	if (InputManager::isKeyDown(KeyCodes::ESC)) glutLeaveMainLoop();

	UpdateMembers(currDelta);

	InputManager::Update();

	glutSetWindow(mainWindow);
	glutPostRedisplay();
}

Camera *GlutManager::GetMainCamera(void){
	return mainCamera;
}

void GlutManager::SetMainCamera(Camera *camera){
	mainCamera = camera;
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


void GlutManager::AddMember(std::string name, IObject *object){
	members[name] = object;
}

void GlutManager::UpdateMembers(float timeDelta){
	std::map<std::string, IObject *>::iterator iter;
	IUpdateable *updateable;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		updateable = dynamic_cast<IUpdateable*>(iter->second);
		if (updateable != 0){
			updateable->Update(timeDelta);
		}
	}

}

float GlutManager::currDelta = 0.0f;