#include "Spawner.h"
#include "openGL.h"

Spawner::Spawner() {

}

Spawner::Spawner(std::vector<WorldSquare> squares) {
	//getting collection of spawn points from currently loaded map
	for (size_t i = 0; i < squares.size(); i++) {
		if (squares[i].type == 3) {
			spawnPoints.push_back(squares[i]);
		}
	}
}

void Spawner::InitialSpawn(std::vector<Player *> players) {
	for (size_t i = 0; i < players.size(); i++) {
		players[i]->Move(spawnPoints[i].x * 8, 0.0f, spawnPoints[i].y * 8);
	}
}

void Spawner::SpawnPlayer(Player *player, std::vector<IGameObject *> players) {
	float dist = 0;
	float temp = 0;
	float posx = 0;
	float posz = 0;
	int pos = 0;
	float maxDist = -FLT_MAX;
	float currDist = 0;
	
	for (size_t i = 0; i < players.size(); i++) {
		posx += ((Player *)players[i])->Position().x;
		posz += ((Player *)players[i])->Position().z;
	}
	posx /= (players.size());
	posz /= (players.size());
	/*
	for (size_t j = 0; j < spawnPoints.size(); j++) {
		temp = glm::sqrt(glm::pow(spawnPoints[j].x - posx, 2) +
			glm::pow(spawnPoints[j].y - posz, 2));
		if (temp > dist) {
			dist = temp;
			pos = j;
		}
	}
	for (size_t j = 0; j < spawnPoints.size(); j++) {
		currDist = glm::length(glm::vec2(posx, posz) - glm::vec2(spawnPoints[j].x, spawnPoints[j].y));
		if (maxDist < currDist)
		{
			maxDist = currDist;
			pos = j;
		}
	}*/

	pos = rand() % spawnPoints.size();

	player->Move(Transform::Inverse(player->Position()));
	player->Move(spawnPoints[pos].x * 8, 0.0f, spawnPoints[pos].y * 8);
	player->ResetStats();
}
