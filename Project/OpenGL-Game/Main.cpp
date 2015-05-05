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
MeshObject myMesh;

GroupObject test;

int main(int argc, char **argv) {
	int menu;
	glutInit(&argc, argv);
	GlutManager::Init(false);
	InputManager::Init();

	char* obj_filename = (char*) "../Assets/Models/floorCube.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	myMesh.Init(obj_filename, v_shader_filename, f_shader_filename);

	
	

	myMesh.Move(1.0f, 0.0f, 0.0f);

	GlutManager::AddMember("MyMesh", &myMesh);
	

	
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

	myMesh.Update(0.0f);
	myMesh.Render();
	myMesh.RenderBoundingBox();

	if (engine.loaded == true) {
		engine.renderWorld();
	}


	glutSwapBuffers();
}
