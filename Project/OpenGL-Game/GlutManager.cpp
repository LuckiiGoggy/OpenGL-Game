#include "openGL.h"
#include <iostream>
#include "GlutManager.h"
#include "IRenderable.h"
#include "InputManager.h"
#include "GLUIManager.h"

std::map<std::string, IObject *> GlutManager::members;
Camera *GlutManager::mainCamera = NULL;
GLint GlutManager::mainWindow;
float GlutManager::currDelta;


void GlutManager::Init(void)
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

	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(GlutManager::RenderScene);
	glutIdleFunc(GlutManager::IdleFunc);
	glutReshapeFunc(GlutManager::Reshape);

	InputManager::Init();

	GLUIManager::initGLUI(GlutManager::mainWindow, GlutManager::IdleFunc);

	currDelta = glutGet(GLUT_ELAPSED_TIME);

	mainCamera = new Camera();
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
			renderable->Render();
		}
	}

	if (GLUIManager::engine.loaded == true) {
		GLUIManager::engine.renderWorld();
	}


	glutSwapBuffers();
}

void GlutManager::IdleFunc(void){

	currDelta = glutGet(GLUT_ELAPSED_TIME) - currDelta;

	if (InputManager::isKeyDown(KeyCodes::ESC)) glutLeaveMainLoop();

	
	if (InputManager::isLeftButtonDown() && GLUIManager::engine.loaded == true) {
		Point p = InputManager::GetMousePos();
		GLUIManager::engine.updateSquare(p, GLUIManager::radiogroup->get_int_val());
	}
	
	
	if (InputManager::isKeyDown(KeyCodes::w)) mainCamera->Move(glm::vec3(0.0f, 0.0f, 0.005f));
	if (InputManager::isKeyDown(KeyCodes::a)) mainCamera->Move(glm::vec3(0.005f, 0.0f, 0.0f));
	if (InputManager::isKeyDown(KeyCodes::s)) mainCamera->Move(glm::vec3(0.0f, 0.0f, -0.005f));
	if (InputManager::isKeyDown(KeyCodes::d)) mainCamera->Move(glm::vec3(-0.005f, 0.0f, 0.0f));
	if (InputManager::isSpecialKeyDown(GLUT_KEY_SHIFT_L)) mainCamera->Move(glm::vec3(0.0f, -0.005f, 0.0f));
	if (InputManager::isKeyDown(KeyCodes::Space)) mainCamera->Move(glm::vec3(0.0f, 0.005f, 0.0f));
	
	if (InputManager::isSpecialKeyDown(GLUT_KEY_LEFT)) mainCamera->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), 0.001f);
	if (InputManager::isSpecialKeyDown(GLUT_KEY_RIGHT)) mainCamera->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), -0.001f);
	if (InputManager::isSpecialKeyDown(GLUT_KEY_UP)) mainCamera->Rotate(glm::vec3(1.0f, 0.0f, 0.0f), 0.001f);
	if (InputManager::isSpecialKeyDown(GLUT_KEY_DOWN)) mainCamera->Rotate(glm::vec3(1.0f, 0.0f, 0.0f), -0.001f);


	if (InputManager::isKeyDown(KeyCodes::m)) mainCamera->ClearRotation();




	//std::cout << "\n In IdleFunc";

	mainCamera->Update(currDelta);

	UpdateMembers(currDelta);

	
	/*
	if (InputManager::isKeyDown(KeyCodes::w)) myMesh.Move(glm::vec3(0.0f, 0.0f, 0.01f));
	if (InputManager::isKeyDown(KeyCodes::a)) myMesh.Move(glm::vec3(-0.01f, 0.0f, 0.0f));
	if (InputManager::isKeyDown(KeyCodes::s)) myMesh.Move(glm::vec3(0.0f, 0.0f, -0.01f));
	if (InputManager::isKeyDown(KeyCodes::d)) myMesh.Move(glm::vec3(0.01f, 0.0f, 0.0f));
	if (InputManager::isSpecialKeyDown(GLUT_KEY_SHIFT_L)) myMesh.Move(glm::vec3(0.0f, -0.01f, 0.0f));
	if (InputManager::isKeyDown(KeyCodes::Space)) myMesh.Move(glm::vec3(0.0f, 0.01f, 0.0f));
	*/
	

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	*/

	GLUIManager::reshape(x, y);


	//glutPostRedisplay();
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