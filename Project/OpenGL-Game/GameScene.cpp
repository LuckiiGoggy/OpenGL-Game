#include "GameScene.h"
#include "MeshObject.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

void GameScene::Init(void){
	char* obj_filename = (char*) "../Assets/Models/suzanne.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	MeshObject *myMesh = new MeshObject();
	
	myMesh->Init(obj_filename, v_shader_filename, f_shader_filename);


	AddMember("MyMesh", myMesh);
}

