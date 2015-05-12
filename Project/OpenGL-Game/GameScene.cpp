#include "GameScene.h"
#include "MeshObject.h"
#include "GlutManager.h"

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
	MeshObject *myMesh2 = new MeshObject();
	myMesh->Init(obj_filename, v_shader_filename, f_shader_filename);
	myMesh2->Init(obj_filename, v_shader_filename, f_shader_filename);
	AddMember("MyMesh", myMesh);
	AddMember("MyMesh2", myMesh2);

	GlutManager::SetPhysEngi(new PhysicsEngine());

	myMesh->Move(0.0f, 0.0f, -5.0f);

	GlutManager::GetPhysEngi()->registerRigidBody(myMesh, myMesh, "Suzanne");

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
		//spawn->SpawnProjectile((Player*)members.at("Player"), this);
	}

	for (size_t i = 0; i < spawn->projectiles.size(); i++){
		(spawn->projectiles[i])->Update(timedelta);
	}


	GlutManager::GetPhysEngi()->updateQuadTree();
	GlutManager::GetPhysEngi()->quadTreeCollision();
	GlutManager::GetPhysEngi()->updateVelocities();
}
