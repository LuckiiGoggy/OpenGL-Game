#ifndef PLAYER_H
#define PLAYER_H

#include "IGameObject.h"
#include "Character.h"
#include "MeshObject.h"
#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\detail\type_vec.hpp"

class Player : public Character
{
public:
	Player(void);
	Player(std::string _name);
	~Player(void);

	void Update(float timeDelta);

	void Shoot(void);
	GLNetwork::Packet *GetPInfoPacket(void);


	virtual void IncStat(std::string statName);
	virtual void DecStat(std::string statName);
	virtual void ResetStats(void);

	void UpdatePInfoPacket(void);

protected:
	float ammoCD;
	float ammoCDTimer;
	GLNetwork::PlayerInfoPacket pInfoPacket;
};

#endif