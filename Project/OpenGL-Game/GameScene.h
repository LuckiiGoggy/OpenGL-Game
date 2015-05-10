#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "IGameObject.h"
#include "WorldEngine.h"
#include "Spawner.h"
#include "Projectile.h"
#include <map>
#include <string>

class GameScene : public Scene
{
public:
	WorldEngine* engine;
	Spawner* spawn;
	std::vector<MeshObject *> players;
	std::vector<Projectile *> projectiles;
	GameScene();
	~GameScene();

	void Init(void);
	void Render();
	void Update(float timedelta);

private:
};

#endif 