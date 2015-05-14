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
#include <map>

class Spawner {
public:
	Spawner();
	Spawner(std::vector<WorldSquare> squares);
	void InitialSpawn(std::vector<Player *> players);
	void SpawnPlayer(MeshObject &player, std::vector<Player *> players);
	void SpawnProjectile(Player* player, IGameObject *scene);

	void RemoveProjectile(std::string);
	void UpdateProjectiles(float timeDelta);
	void RenderProjectiles();

	bool IsProjectileActive(std::string);

	/*Move to private/protected*/
	std::vector<WorldSquare> spawnPoints;

	//Gee Self Note: Could use a GroupObject instead... Maybe..
	std::map<std::string, Projectile *> projectiles;
	static int projCount;
	MeshObject* projectileMesh;
};

#endif
