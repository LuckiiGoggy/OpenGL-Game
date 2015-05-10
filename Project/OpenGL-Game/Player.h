#ifndef PLAYER_H
#define PLAYER_H

#include "IGameObject.h"
#include "Character.h"
#include "CharacterController.h"
#include "IRenderable.h"
#include "MeshObject.h"
#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies\glm\glm\detail\type_vec.hpp"

class Player : public IGameObject, public IRenderable
{
public:
	Player(void);
	~Player(void);

	virtual void Update(float timeDelta);
	virtual void Render(void);
	glm::vec3 Position(void);

	Character *Chara(void);

private:
	Character *chara;
	CharacterController *controller;
	int delta;
	int lastMouseX;
	int lastMouseY;
	
};

#endif