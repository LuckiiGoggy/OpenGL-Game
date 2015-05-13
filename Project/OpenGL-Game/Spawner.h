#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "openGL.h"
#include "MeshObject.h"
#include "WorldSquare.h"
#include "Player.h"
#include "Projectile.h"
#include <limits>
#include <string>
#include "GameObjectContainer.h"
#include "GroupObject.h"

class Spawner {
public:
	Spawner();
	Spawner(std::vector<WorldSquare> squares, std::vector<MeshObject *> players);
	void InitialSpawn();
	void SpawnPlayer(MeshObject &player, std::vector<MeshObject *> players);
	void SpawnProjectile(Player* player, GameObjectContainer *scene);
	std::vector<WorldSquare> spawnPoints;
	std::vector<Projectile *> projectiles;
	static int projCount;
	MeshObject* projectileMesh;
};

#endif
