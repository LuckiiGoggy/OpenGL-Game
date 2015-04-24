

#ifndef CQDEMO01_H
#define CQDEMO01_H

#include "openGL.h"
#include "Quadtree.h"


class CQDemo01
{
public:
	CQDemo01();
	void init();
	void beginDemo();

	void renderDemo1();

	void moveObjects();

	void drawRect(Rect r);
	void drawRect(Rect r, glm::vec3 color);
	void drawRectBounds(Rect r, glm::vec3 color);

	glm::vec3 calcRelativePoints2D(int x, int y, int screenWidth, int screenHeight);

	Quadtree quad;

	Rect objects[11];

	int i;
	int numOfObjects;
	int screenW;
	int screenH;

	glm::vec3 blue;
	glm::vec3 green;
	glm::vec3 red;
	glm::vec3 purple;
	glm::vec3 yellow;
	glm::vec3 cyan;
	glm::vec3 black;

};


#endif

