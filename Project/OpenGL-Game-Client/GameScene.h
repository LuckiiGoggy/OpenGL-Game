#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "IGameObject.h"
#include "WorldEngine.h"
#include "Spawner.h"
#include "Projectile.h"
#include <map>
#include <string>
#include <vector>
#include "PhysicsEngine.h"

class GameScene : public Scene
{
public:
	WorldEngine* engine;
	Spawner* spawn;
	std::vector<MeshObject *> players;
	std::vector<Projectile *> projectiles;
	GameScene();
	~GameScene();
	PhysicsEngine physEngi;


	void Init(void);
	void Render();
	void Update(float timedelta);

	void RegisterNewProjectile(std::string);

protected:
	std::vector<std::string> projectileIds;
};

#endif 