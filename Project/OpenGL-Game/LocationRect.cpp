
#include "LocationRect.h"

LocationRect::LocationRect(void)
{
	sx = 0;
	sy = 0;
	ex = 0;
	ey = 0;

	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	color = glm::vec3(r, g, b);

	id = -1;
}
LocationRect::LocationRect(int xs, int ys, int xe, int ye)
{
	sx = xs;
	sy = ys;
	ex = xe;
	ey = ye;

	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	color = glm::vec3(r, g, b);

	id = -1;
}
LocationRect::LocationRect(int xs, int ys, int xe, int ye, glm::vec3 c)
{
	sx = xs;
	sy = ys;
	ex = xe;
	ey = ye;

	r = c.x;
	g = c.y;
	b = c.z;
	color = c;

	id = -1;
}
LocationRect::LocationRect(int xs, int ys, int xe, int ye, int id_)
{
	sx = xs;
	sy = ys;
	ex = xe;
	ey = ye;

	r = 1.0f;
	g = 0.0f;
	b = 0.0f;
	color = glm::vec3(r, g, b);

	id = id_;
	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

}
LocationRect::LocationRect(int xs, int ys, int xe, int ye, glm::vec3 c, int id_)
{
	sx = xs;
	sy = ys;
	ex = xe;
	ey = ye;

	r = c.x;
	g = c.y;
	b = c.z;
	color = c;

	id = id_;
	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

}
LocationRect::LocationRect(int xs, int ys, int xe, int ye, float r_, float g_, float b_, int id_)
{
	sx = xs;
	sy = ys;
	ex = xe;
	ey = ye;

	r = r_;
	g = g_;
	b = b_;

	color = glm::vec3(r, g, b);

	id = id_;
	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

}

void LocationRect::move(int x, int y)
{
	sx += x;
	sy += y;
	ex += x;
	ey += y;
}
void LocationRect::move(int x, int y, int z)
{
	sx += x;
	sy += y;
	ex += x;
	ey += y;
}

void LocationRect::setColor(float r_, float g_, float b_)
{
	r = r_;
	g = g_;
	b = b_;
	color = glm::vec3(r, g, b);
}
void LocationRect::setColor(glm::vec3 c)
{
	r = c.x;
	g = c.y;
	b = c.z;
	color = c;
}
int LocationRect::getWidth()
{
	int w = (ex - sx);
	return abs(w);
}
int LocationRect::getHeight()
{
	int h = (ey - sy);
	return abs(h);
}

