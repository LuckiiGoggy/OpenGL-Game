#ifndef RECT_H
#define RECT_H

#include "BoundingBox.h"

#include "Math.h"
#include "Dependencies\glm\glm\glm.hpp"


class Rect
{
public:

	Rect();
	Rect(int sx, int sy, int ex, int ey);
	Rect(int sx, int sy, int ex, int ey, glm::vec3 color);
	Rect(int sx, int sy, int ex, int ey, glm::vec3 color, int id_);
	Rect(int xs, int ys, int xe, int ye, float r_, float g_, float b_, int id_);

	void move(int x, int y);

	int getWidth();
	int getHeight();

	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

	BoundingBox Bbox;

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
