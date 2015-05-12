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

	engine = new WorldEngine();
	//engine->readWorld("level");

	spawn = new Spawner(engine->squares, players);
}

void GameScene::Render() {
	Scene::Render();
	//engine->renderWorld();
	for (size_t i = 0; i < spawn->projectiles.size(); i++) {
		(spawn->projectiles[i])->Render();
	}	
}

void GameScene::Update(float timedelta) {
	Scene::Update(timedelta);
	if (InputManager::IsMouseClicked(timedelta)) {
		spawn->SpawnProjectile((Player*)members.at("Player"), this);
	}

	for (size_t i = 0; i < spawn->projectiles.size(); i++){
		(spawn->projectiles[i])->Update(timedelta);
	}

}
