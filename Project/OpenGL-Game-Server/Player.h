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
	~Player(void);
protected:
	
};

#endif