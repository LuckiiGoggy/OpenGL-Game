
#include "Rect.h"

Rect::Rect()
{
	sx = 0;
	sy = 0;
	ex = 0;
	ey = 0;

	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	color = glm::vec3(r, g, b);
}
Rect::Rect(int xs, int ys, int xe, int ye)
{
	sx = xs;
	sy = ys;
	ex = xe;
	ey = ye;

	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	color = glm::vec3(r, g, b);
}
Rect::Rect(int xs, int ys, int xe, int ye, glm::vec3 c)
{
	sx = xs;
	sy = ys;
	ex = xe;
	ey = ye;

	r = c.x;
	g = c.y;
	b = c.z;
	color = c;
}
void Rect::setColor(float r_, float g_, float b_)
{
	r = r_;
	g = g_;
	b = b_;
	color = glm::vec3(r, g, b);
}
void Rect::setColor(glm::vec3 c)
{
	r = c.x;
	g = c.y;
	b = c.z;
	color = c;
}
int Rect::getWidth()
{
	int w = (ex - sx);
	return abs(w);
}
int Rect::getHeight()
{
	int h = (ey - sy);
	return abs(h);
}

