
#include "RectObject.h"

RectObject::RectObject()
:Rect()
{
	//call parent constructor
	
	velocities = std::vector<Velocity*>();
	mass = 1;
}
RectObject::RectObject(int sx, int sy, int ex, int ey)
:Rect(sx, sy, ex, ey)
{
	velocities = std::vector<Velocity*>();
	mass = 1;
}
RectObject::RectObject(int sx, int sy, int ex, int ey, glm::vec3 color)
:Rect(sx, sy, ex, ey, color)
{
	velocities = std::vector<Velocity*>();
	mass = 1;
}
RectObject::RectObject(int sx, int sy, int ex, int ey, glm::vec3 color, int id_)
:Rect(sx, sy, ex, ey, color, id_)
{
	velocities = std::vector<Velocity*>();
	mass = 1;
}
RectObject::RectObject(int sx, int sy, int ex, int ey, float r_, float g_, float b_, int id_)
:Rect(sx, sy, ex, ey, r_, g_, b_, id_)
{
	velocities = std::vector<Velocity*>();
	mass = 1;
}
RectObject::RectObject(Rect* rect)
{
	Bbox = rect->Bbox;

	sx = rect->sx;
	sy = rect->sy;
	ex = rect->ex;
	ey = rect->ey;

	r = rect->r;
	g = rect->g;
	b = rect->b;
	color = rect->color;

	id = rect->id;
	id_c = rect->id_c;
	//const unsigned char temp = *rect.id_c;
	//id_c = &temp;

	delete(rect);

	velocities = std::vector<Velocity*>();
	mass = 1;
}
RectObject::RectObject(Rect rect)
{
	Bbox = rect.Bbox;

	sx = rect.sx;
	sy = rect.sy;
	ex = rect.ex;
	ey = rect.ey;

	r = rect.r;
	g = rect.g;
	b = rect.b;
	color = rect.color;

	id = rect.id;
	id_c = rect.id_c;
	//const unsigned char temp = *rect.id_c;
	//id_c = &temp;

	velocities = std::vector<Velocity*>();
	mass = 1;
}
void RectObject::addVelocity(Velocity* f)
{
	velocities.push_back(f);
}