#include "Spawner.h"
#include "GlutManager.h"

int Spawner::projCount;

Spawner::Spawner() {

}

Spawner::Spawner(std::vector<WorldSquare> squares, std::vector<MeshObject *> players) {
	//getting collection of spawn points from currently loaded map
	for (size_t i = 0; i < squares.size(); i++) {
		if (squares[i].type == 3) {
			spawnPoints.push_back(squares[i]);
		}
	}
	for (size_t j = 0; j < players.size(); j++) {
		players[j]->Move(squares[j].x, 0.0f, squares[j].y);
	}

	projCount = 0;
	projectile;
}

void Spawner::InitialSpawn() {

}

void Spawner::SpawnPlayer(MeshObject &player, std::vector<MeshObject *> players) {
	float dist = std::numeric_limits<float>::max();
	float temp = 0;
	float posx = 0;
	float posy = 0;
	int pos = 0;
	for (size_t i = 0; i < players.size(); i++) {
		//posx += players[i].sumTranslation[0][3];
		//posy += players[i].sumTranslation[1][3];
	}
	posx /= players.size();
	posy /= players.size();
	for (size_t j = 0; j < spawnPoints.size(); j++) {
		temp = glm::sqrt(glm::pow(spawnPoints[j].x - posx, 2) +
			glm::pow(spawnPoints[j].y - posy, 2));
		if (temp > dist) {
			dist = temp;
			pos = j;
		}
	}
	//player.MoveTo(spawnPoints[pos].x, 0.0f, spawnPoints[pos].y);
}

void Spawner::SpawnProjectile(Player* player, GameObjectContainer *scene) {
	/*Create a new projectile with
	direction and position based
	on player that spawned it*/

	glm::vec3 v = (dynamic_cast<Transform *>(player->Chara()->GetMember("BoxMan")))->Position();
	glm::mat4 m = (dynamic_cast<Transform *>(player->Chara()->GetMember("BoxMan")))->NetRotation();
	Projectile *newProj = new Projectile(m, v);
	glm::vec3 vdir = Transform::ApplyTransVec3(glm::vec3(0.0f, 0.0f, -1.0f), m);
	Velocity* vel = new Velocity(vdir.x, vdir.y, vdir.z, 1, 10);
	projCount++;
	std::string name = "projectile" + std::to_string(projCount);
	GlutManager::GetPhysEngi()->registerRigidBody(newProj, newProj, name, 1, projCount);
	GlutManager::GetPhysEngi()->addVelocityTo(name, vel);
	projectiles.push_back(newProj);
}
