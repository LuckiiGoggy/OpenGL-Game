#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#pragma once

#include "CharacterController.h"
#include "Player.h"
class PlayerController : public CharacterController
{
public:
	PlayerController(Player *);
	~PlayerController();
	virtual void Update(float timeDelta);

protected:
	int test;
	float lastMouseX;
	float lastMouseY;
};

#endif