#include "GameScene.h"
#include "MeshObject.h"
#include "GlutManager.h"
#include "PlayerController.h"
#include "Overlay2D.h"
#include "ClientGame.h"

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
	ClientGame::update(2);

	if (members.find("Player") != members.end()){
		GLNetwork::PlayerPacket playerPacket;

		if (InputManager::isKeyDown(KeyCodes::w)) playerPacket.forward = true;
		if (InputManager::isKeyDown(KeyCodes::s)) playerPacket.backward = true;
		if (InputManager::isKeyDown(KeyCodes::a)) playerPacket.left = true;
		if (InputManager::isKeyDown(KeyCodes::d)) playerPacket.right = true;

		if (InputManager::IsMouseClicked(timedelta)) playerPacket.isShooting = true;
		Transform *transformable = dynamic_cast<Transform *>(GetMember("Player"));
		if (transformable != 0){
			playerPacket.netRot00 = (transformable->NetRotation())[0][0];
			playerPacket.netRot01 = (transformable->NetRotation())[0][1];
			playerPacket.netRot02 = (transformable->NetRotation())[0][2];
			playerPacket.netRot10 = (transformable->NetRotation())[1][0];
			playerPacket.netRot11 = (transformable->NetRotation())[1][1];
			playerPacket.netRot12 = (transformable->NetRotation())[1][2];
			playerPacket.netRot20 = (transformable->NetRotation())[2][0];
			playerPacket.netRot21 = (transformable->NetRotation())[2][1];
			playerPacket.netRot22 = (transformable->NetRotation())[2][2];
		}
		
		ClientGame::SendPacket(GLNetwork::PLAYER_PACKET, &playerPacket);
	}

	Scene::Update(timedelta);

}

void GameScene::UpdateTransformObj(int objId, MeshTypes m_type, glm::mat4 &rot, glm::vec3 pos)
{
	std::map<int, std::string>::iterator iter = objIdStrId.find(objId);

	if (iter != objIdStrId.end()){
		Transform *transformable = dynamic_cast<Transform *>(GetMember(iter->second));
		if (transformable != 0){
			transformable->NetRotation(rot);
			transformable->MoveTo(pos);
		}
	}
	else{
		CreateNewObj(objId, m_type, rot, pos);
	}
}

void GameScene::CreateNewObj(int objId, MeshTypes m_type, glm::mat4 &rot, glm::vec3 pos)
{
	std::string name = std::to_string(objId);
	IGameObject *newObj = new Player();/*GameObjectLibrary::NewWall*/;

	objIdStrId[objId] = name;

	switch (m_type)
	{
	case Wall:
		/* newObj = GameObjectLibrary::NewWall(); */
		break;
	case Floor:
		/* newObj = GameObjectLibrary::NewFloor(); */
		break;
	case BoxMan:
		newObj = new Player();
		break;
	case Spear:
		/* newObj = GameObjectLibrary::NewSpear(); */
		break;
	}

	AddMember(name, newObj);


	Transform *transformable = dynamic_cast<Transform *>(newObj);
	if (transformable != 0){
		transformable->NetRotation(rot);
		transformable->MoveTo(pos);
	}
}

void GameScene::UpdatePlayerInfo(int objId, int health, int ammo, int score)
{
	std::map<int, std::string>::iterator iter = objIdStrId.find(objId);

	if (iter != objIdStrId.end()){
		Player *player = dynamic_cast<Player *>(GetMember(iter->second));
		if (player != 0){
			player->SetStatValue("Health", health);
			player->SetStatValue("Ammo", ammo);
			player->SetStatValue("Score", score);

			HUD.setAmmo(ammo);
			HUD.setHP(health);
			HUD.setScore(score);
		}
	}
	else{
		CreateNewActivePlayer(objId, health, ammo, score);
	}
}

void GameScene::CreateNewActivePlayer(int objId, int health, int ammo, int score)
{
	Player *player = new Player();
	PlayerController *pC = new PlayerController(player);

	player->SetStatValue("Health", health);
	player->SetStatValue("Ammo", ammo);
	player->SetStatValue("Score", score);

	HUD.setAmmo(ammo);
	HUD.setHP(health);
	HUD.setScore(score);


	AddMember("Player", player);
	AddMember("Controller", pC);

	objIdStrId[objId] = "Player";
}
