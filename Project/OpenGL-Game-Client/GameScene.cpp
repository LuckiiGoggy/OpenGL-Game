#include "GameScene.h"
#include "MeshObject.h"
#include "GlutManager.h"
#include "PlayerController.h"
#include "Overlay2D.h"

Overlay2D HUD;

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

	myMesh->Move(0.0f, 0.0f, -8.0f);
	Player *player = new Player();
	AddMember("Player", player);
	players.push_back(player);

	Player *player2 = new Player();
	AddMember("Player2", player2);
	players.push_back(player2);

	Player *player3 = new Player();
	AddMember("Player3", player3);
	players.push_back(player3);

	Player *player4 = new Player();
	AddMember("Player4", player4);
	players.push_back(player4);
	pC = new PlayerController(player);

	AddMember("Controller", pC);

}

void GameScene::Render() {
	Scene::Render();

	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	HUD.prepare2D(m_viewport[0], m_viewport[1], m_viewport[2], m_viewport[3]);
	HUD.Render();
}

void GameScene::Update(float timedelta) {


// 	for (size_t counter = 0; counter < projectileIds.size(); counter++){
// 
// 		for (size_t counter2 = 0; counter2 < collidedWith.size(); counter2++){
// 			Player *player = dynamic_cast<Player *> (collidedWith[counter2]);
// 
// 			if (player != 0){
// 				player->DecStat("Health");
// 				HUD.decreaseHP();
// 			}
// 		}
// 
// 	}


// 
// 	if (InputManager::IsMouseClicked(timedelta) && ((Player*)members.at("Player"))->GetStatValue("Ammo") > 0) {
// 		spawn->SpawnProjectile((Player*)members.at("Player"), this);
// 		((Player*)members.at("Player"))->DecStat("Ammo");
// 		HUD.decreaseAmmo();
// 	}

	Scene::Update(timedelta);

}
