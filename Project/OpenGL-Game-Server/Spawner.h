#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "openGL.h"
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
	Spawner(std::vector<WorldSquare> squares);
	void InitialSpawn(std::vector<Player *> players);
	void SpawnPlayer(Player *player, std::vector<IGameObject *> players);

	/*Move to private/protected*/
	std::vector<WorldSquare> spawnPoints;
};

#endif
