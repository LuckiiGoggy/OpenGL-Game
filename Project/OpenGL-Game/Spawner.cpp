#include "Spawner.h"

Spawner::Spawner() {
	//getting collection of spawn points from currently loaded map
	for (int i = 0; i < GLUIManager::engine.squares.size(); i++) {
		if (GLUIManager::engine.squares[i].type == 3) {
			spawnPoints.push_back(GLUIManager::engine.squares[i]);
		}
	}
	/*for all players {
		set position to a spawn point
	}
	*/
}

void Spawner::SpawnPlayer() {
	/*for all players {
		add/average/apply heuristic to player's positions
	}
	for all spawnPoints {
		compare place to spawn player to spawnPoint coordinates
	}
	move player to spawnPoint
	*/
}

void Spawner::SpawnProjectile() {
	/*Create a new projectile with 
		direction and position based 
		on player that spawned it
	*/
}
