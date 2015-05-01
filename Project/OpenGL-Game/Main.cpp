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

void updateGame();
void menuEvents(int choice);
void renderScene(void);
MeshObject myMesh;

GroupObject test;

int main(int argc, char **argv) {
	int menu;
	glutInit(&argc, argv);
	GlutManager::Init();
	char* obj_filename = (char*) "../Assets/Models/spear.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/gouraud-shading-two-sided.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/gouraud-shading-two-sided.f.glsl";

	myMesh.Init(obj_filename, v_shader_filename, f_shader_filename);


	GlutManager::AddMember("MyMesh", &myMesh);
	InputManager::Init();

	GLUIManager::initGLUI(GlutManager::mainWindow, GlutManager::IdleFunc);

	GlutManager::StartLoop();

	glutMainLoop();

	return 0;
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);

	myMesh.Update(0.0f);
	myMesh.Render();
	myMesh.RenderBoundingBox();

	glutSwapBuffers();
}
