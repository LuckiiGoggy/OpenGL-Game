#ifndef CQDEMO02_H
#define CQDEMO02_H

#include "openGL.h"
#include "InputManager.h"
#include "IObject.h"
#include "IUpdateable.h"
#include "MeshObject.h"
#include "RigidBody.h"
#include "GlutManager.h"
#include "MeshObject.h"

#include "PhysicsEngine.h"


#include <iostream>
#include <vector>

class CQDemo02 : public IObject, public IRenderable
{
public:
	CQDemo02();
	void init();
	void initObjects();

	void Render();
	void Update(float timeDelta);
	void renderSummon();

	void drawRect(LocationRect r);
	void drawRect(LocationRect r, glm::vec3 color);
	void drawRect(LocationRect r, bool DRAWID);
	void drawRect(LocationRect r, glm::vec3 color, bool DRAWID);
	void drawRectBounds(LocationRect r);
	void drawRectBounds(LocationRect r, glm::vec3 color);

	glm::vec3 calcRelativePoints2D(int x, int y, int screenWidth, int screenHeight);

	PhysicsEngine physicsEngine;

	bool summon4;
	bool summon3;
	bool summon2;
	bool summon1;
	bool summon0;

	int last_ticks;
	int delta_t;

	int i;
	int numOfObjects;

	int screenW;
	int screenH;
	int screenD;

	glm::vec3 blue;
	glm::vec3 green;
	glm::vec3 red;
	glm::vec3 purple;
	glm::vec3 yellow;
	glm::vec3 cyan;
	glm::vec3 black;

};

#endif