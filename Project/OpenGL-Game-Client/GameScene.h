#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "openGL.h"

#include "Scene.h"
#include "IGameObject.h"
#include "Projectile.h"
#include <map>
#include <string>
#include <vector>
#include "Player.h"

class GameScene : public Scene
{
public:
	enum MeshTypes{ Wall, Floor, BoxMan, Spear };

	std::vector<Player *> players;
	GameScene();
	~GameScene();


	void Init(void);
	void Render();
	void Update(float timedelta);

	void UpdateTransformObj(int objId, MeshTypes m_type, glm::mat4 &rot, glm::vec3 pos);
	void CreateNewObj(int objId, MeshTypes m_type, glm::mat4 &rot, glm::vec3 pos);

	void UpdatePlayerInfo(int objId, int health, int ammo, int score);
	void CreateNewActivePlayer(int objId, int health, int ammo, int score);



protected:
	std::map<int, std::string> objIdStrId;




};

#endif 