
#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include "Rect.h"
#include "Velocity.h"
#include <vector>

class RectObject:public Rect
{
public:
	RectObject();
	RectObject(Rect rect);
	RectObject(Rect* rect);
	RectObject(int sx, int sy, int ex, int ey);
	RectObject(int sx, int sy, int ex, int ey, glm::vec3 color);
	RectObject(int sx, int sy, int ex, int ey, glm::vec3 color, int id_);
	RectObject(int xs, int ys, int xe, int ye, float r_, float g_, float b_, int id_);


	void addVelocity(Velocity* f);

	std::vector<Velocity*> velocities;
	float mass;

};

#endif