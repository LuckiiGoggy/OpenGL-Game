#ifndef PLAYER_H
#define PLAYER_H

#include "IGameObject.h"
#include "Character.h"
#include "CharacterController.h"
#include "IRenderable.h"
#include "MeshObject.h"

class Player : public IGameObject, public IRenderable
{
public:
	Player(void);
	~Player(void);

	virtual void Update(float timeDelta);
	virtual void Render(void);

	MeshObject *mesh;

private:
	Character *chara;
	CharacterController *controller;
	
};

#endif