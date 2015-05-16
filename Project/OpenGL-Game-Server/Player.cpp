#include "Player.h"
#include "GroupObject.h"
#include "MeshObject.h"

Player::Player(void)
{
	AddStat(CharacterStat("Score", 0, 0));
	AddStat(CharacterStat("Health", 3, 0, 3));
	AddStat(CharacterStat("Ammo", 3, 0, 3));
}


Player::~Player(void)
{
	
}

