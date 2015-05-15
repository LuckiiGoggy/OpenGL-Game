#ifndef LOCATIONRECT_H
#define LOCATIONRECT_H

#include "Math.h"
#include "Dependencies\glm\glm\glm.hpp";

class LocationRect
{
public:
	LocationRect();
	LocationRect(float sx, float sy, float ex, float ey);
	LocationRect(float sx, float sy, float ex, float ey, int id_);
	LocationRect(float sx, float sy, float ex, float ey, glm::vec3 color);
	LocationRect(float sx, float sy, float ex, float ey, glm::vec3 color, int id_);
	LocationRect(float xs, float ys, float xe, float ye, float r_, float g_, float b_, int id_);

	void move(float x, float y);
	void move(float x, float y, float z);

	float getWidth();
	float getHeight();

	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

	int id;
	const unsigned char * id_c;

	float sx;
	float sy;
	float ex;
	float ey;

	float r;
	float g;
	float b;
	glm::vec3 color;
};
#endif