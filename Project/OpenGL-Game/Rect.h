#ifndef RECT_H
#define RECT_H

#include "Math.h"
#include "Dependencies\glm\glm\glm.hpp";

class Rect
{
public:

	Rect();
	Rect(int sx, int sy, int ex, int ey);
	Rect(int sx, int sy, int ex, int ey, glm::vec3 color);

	int getWidth();
	int getHeight();

	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

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
