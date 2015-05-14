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

	spawn->RenderProjectiles();
}

void GameScene::Update(float timedelta) {
	GlutManager::GetPhysEngi()->updateQuadTree();
	GlutManager::GetPhysEngi()->ApplyVelocities(timedelta);
	GlutManager::GetPhysEngi()->bruteCollision();


	for (size_t counter = 0; counter < projectileIds.size(); counter++){
		std::string currProjectile = projectileIds[counter];
		std::vector<Transform *> collidedWith = GlutManager::GetPhysEngi()->listCollisionsTransform(currProjectile);

		if (collidedWith.size() > 0 || !spawn->IsProjectileActive(currProjectile)){
			GlutManager::GetPhysEngi()->unregisterRigidBody(currProjectile);
			spawn->RemoveProjectile(currProjectile);
			projectileIds.erase(projectileIds.begin() + counter);
			counter--;
			((Player*)members.at("Player"))->IncStat("Ammo");
		}

		for (size_t counter2 = 0; counter2 < collidedWith.size(); counter2++){
			Player *player = dynamic_cast<Player *> (collidedWith[counter2]);

			if (player != 0)
				player->DecStat("Health");
		}

	}



	if (InputManager::IsMouseClicked(timedelta) && ((Player*)members.at("Player"))->GetStatValue("Ammo") > 0) {
		spawn->SpawnProjectile((Player*)members.at("Player"), this);
		((Player*)members.at("Player"))->DecStat("Ammo");
	}

	spawn->UpdateProjectiles(timedelta);

	GlutManager::GetPhysEngi()->updateVelocities();
	GlutManager::GetPhysEngi()->ApplyVelocities(timedelta);
	GlutManager::GetPhysEngi()->updateVelocities();

	Scene::Update(timedelta);

}

void GameScene::RegisterNewProjectile(std::string id)
{
	projectileIds.push_back(id);
}
