#ifndef LOCATIONRECT_H
#define LOCATIONRECT_H

#include "Math.h"
#include "Dependencies\glm\glm\glm.hpp";

class LocationRect
{
public:
	LocationRect(void);
	LocationRect(int sx, int sy, int ex, int ey);
	LocationRect(int sx, int sy, int ex, int ey, int id_);
	LocationRect(int sx, int sy, int ex, int ey, glm::vec3 color);
	LocationRect(int sx, int sy, int ex, int ey, glm::vec3 color, int id_);
	LocationRect(int xs, int ys, int xe, int ye, float r_, float g_, float b_, int id_);

	void move(int x, int y);
	void move(int x, int y, int z);

	int getWidth();
	int getHeight();

	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

	int id;
	const unsigned char * id_c;

	int sx;
	int sy;
	int ex;
	int ey;

	float r;
	float g;
	float b;
	glm::vec3 color;
};
#endif