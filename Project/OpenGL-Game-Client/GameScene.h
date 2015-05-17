#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "IGameObject.h"
#include "Projectile.h"
#include <map>
#include <string>
#include <vector>
#include "Player.h"
#include "ClientGame.h"

class GameScene : public Scene
{
public:
	std::vector<Player *> players;
	GameScene();
	~GameScene();


	void Init(void);
	void Render();
	void Update(float timedelta);


protected:
	ClientGame *client;
};

#endif 