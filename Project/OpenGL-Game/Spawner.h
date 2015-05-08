#ifndef _SPAWNER_H_
#define _SPAWNER_H_
#include "openGL.h"
#include "MeshObject.h"
#include "WorldEngine.h"
#include "WorldSquare.h"
#include "GLUIManager.h"

class Spawner {
public:
	Spawner();
	void SpawnPlayer();
	void SpawnProjectile();
	std::vector<WorldSquare> spawnPoints;
};

#endif
