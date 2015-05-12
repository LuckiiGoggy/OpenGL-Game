
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

	id = -1;

	Bbox = BoundingBox(glm::vec3(sx, sy, 1), glm::vec3(sx, ey, 1), glm::vec3(ex, ey, 1), glm::vec3(ex, ey, 1),
						glm::vec3(sx, sy, 2), glm::vec3(sx, ey, 2), glm::vec3(ex, ey, 2), glm::vec3(ex, ey, 2));
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

	id = -1;
	/*char *intStr = new char;
	_itoa_s(id, intStr, 1, 10);
	id_c = (const unsigned char *)intStr;//*/

	Bbox = BoundingBox(glm::vec3(sx, sy, 1), glm::vec3(sx, ey, 1), glm::vec3(ex, ey, 1), glm::vec3(ex, ey, 1),
		glm::vec3(sx, sy, 2), glm::vec3(sx, ey, 2), glm::vec3(ex, ey, 2), glm::vec3(ex, ey, 2));
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

	id = -1;
	/*char *intStr = new char;
	_itoa_s(id, intStr, 1, 10);
	id_c = (const unsigned char *)intStr;//*/

	Bbox = BoundingBox(glm::vec3(sx, sy, 1), glm::vec3(sx, ey, 1), glm::vec3(ex, ey, 1), glm::vec3(ex, ey, 1),
		glm::vec3(sx, sy, 2), glm::vec3(sx, ey, 2), glm::vec3(ex, ey, 2), glm::vec3(ex, ey, 2));
}
Rect::Rect(int xs, int ys, int xe, int ye, glm::vec3 c, int id_)
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

	Bbox = BoundingBox(glm::vec3(sx, sy, 1), glm::vec3(sx, ey, 1), glm::vec3(ex, ey, 1), glm::vec3(ex, ey, 1),
		glm::vec3(sx, sy, 4), glm::vec3(sx, ey, 4), glm::vec3(ex, ey, 4), glm::vec3(ex, ey, 4));
}
Rect::Rect(int xs, int ys, int xe, int ye, float r_, float g_, float b_, int id_)
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

	Bbox = BoundingBox(glm::vec3(sx, sy, 1), glm::vec3(sx, ey, 1), glm::vec3(ex, ey, 1), glm::vec3(ex, ey, 1),
		glm::vec3(sx, sy, 4), glm::vec3(sx, ey, 4), glm::vec3(ex, ey, 4), glm::vec3(ex, ey, 4));
}

void Rect::move(int x, int y)
{
	sx += x;
	sy += y;
	ex += x;
	ey += y;

	Bbox.translate(x, y, 0);
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

