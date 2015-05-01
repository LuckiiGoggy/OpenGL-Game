

#ifndef CQDEMO01_H
#define CQDEMO01_H

#include "openGL.h"
#include "Quadtree.h"
#include "InputManager.h"
#include "Collisions.h"
#include "PhysicsEngine.h"

#include <iostream>
#include <vector>


class CQDemo01
{
public:
	CQDemo01();
	void init();
	void initObjects();

	void renderDemo1();
	void renderSummon();

	void moveObjects();

	void drawRect(Rect r);
	void drawRect(Rect r, glm::vec3 color);
	void drawRect(Rect r, bool DRAWID);
	void drawRect(Rect r, glm::vec3 color, bool DRAWID);
	void drawRectBounds(Rect r);
	void drawRectBounds(Rect r, glm::vec3 color);

	glm::vec3 calcRelativePoints2D(int x, int y, int screenWidth, int screenHeight);

	Quadtree quad;
	Collisions collision;
	PhysicsEngine physicsEngine;

	//Rect objects[11];
	std::vector<RectObject*> rectObjects;

	bool summon9;
	bool summon3;
	bool summon1;
	bool summon0;

	bool pause;

	int last_ticks;
	int delta_t;

	int i;
	int numOfObjects;
	int screenW;
	int screenH;

	int timerDelayCounter;
	int timerDelay;

	glm::vec3 blue;
	glm::vec3 green;
	glm::vec3 red;
	glm::vec3 purple;
	glm::vec3 yellow;
	glm::vec3 cyan;
	glm::vec3 black;

};


#endif

