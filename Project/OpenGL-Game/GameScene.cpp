#include "GameScene.h"
#include "MeshObject.h"
#include "GlutManager.h"
#include "PlayerController.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

void GameScene::Init(void){
	char* obj_filename = (char*) "../Assets/Models/floorCube.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/new-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/new-shading.f.glsl";

	MeshObject *myMesh = new MeshObject();
	MeshObject *myMesh2 = new MeshObject();
	PlayerController *pC;
	myMesh->Init(obj_filename, v_shader_filename, f_shader_filename);
	myMesh2->Init(obj_filename, v_shader_filename, f_shader_filename);
	AddMember("MyMesh", myMesh);
	AddMember("MyMesh2", myMesh2);

	GlutManager::SetPhysEngi(new PhysicsEngine());

	myMesh->Move(0.0f, 0.0f, -8.0f);

	GlutManager::GetPhysEngi()->registerRigidBody(myMesh, myMesh, "Suzanne");

	Player *player = new Player();
	AddMember("Player", player);




	GlutManager::GetPhysEngi()->registerRigidBody(player->GetCollisionMesh(), player, "BoxMan");



	pC = new PlayerController(player);

	AddMember("Controller", pC);



	engine = new WorldEngine();
	engine->readWorld("level");

	spawn = new Spawner(engine->squares, players);



}

void GameScene::Render() {
	Scene::Render();
	engine->renderWorld();
	for (size_t i = 0; i < spawn->projectiles.size(); i++) {
		(spawn->projectiles[i])->Render();
	}	
}

void GameScene::Update(float timedelta) {
	GlutManager::GetPhysEngi()->updateQuadTree();
	GlutManager::GetPhysEngi()->ApplyVelocities(timedelta);
	GlutManager::GetPhysEngi()->bruteCollision();
	GlutManager::GetPhysEngi()->updateVelocities();
	GlutManager::GetPhysEngi()->ApplyVelocities(timedelta);
	GlutManager::GetPhysEngi()->updateVelocities();
	Scene::Update(timedelta);


	for (size_t counter = 0; counter < projectileIds.size(); counter++){
		//if (GlutManager::GetPhysEngi()->listCollisions())
	}



	if (InputManager::IsMouseClicked(timedelta)) {
		spawn->SpawnProjectile((Player*)members.at("Player"), this);
	}

	for (size_t i = 0; i < spawn->projectiles.size(); i++){
		(spawn->projectiles[i])->Update(timedelta);
	}
	

}
