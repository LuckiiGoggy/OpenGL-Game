
#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	v1 = glm::vec3(0.0f, 0.0f, 0.0f);
	v2 = glm::vec3(0.0f, 0.0f, 0.0f);
	v3 = glm::vec3(0.0f, 0.0f, 0.0f);
	v4 = glm::vec3(0.0f, 0.0f, 0.0f);
	v5 = glm::vec3(0.0f, 0.0f, 0.0f);
	v6 = glm::vec3(0.0f, 0.0f, 0.0f);
	v7 = glm::vec3(0.0f, 0.0f, 0.0f);
	v8 = glm::vec3(0.0f, 0.0f, 0.0f);

	refresh();
}
BoundingBox::BoundingBox(glm::vec3 v1_, glm::vec3 v2_, glm::vec3 v3_, glm::vec3 v4_,
						 glm::vec3 v5_, glm::vec3 v6_, glm::vec3 v7_, glm::vec3 v8_)
{
	v1 = v1_;
	v2 = v2_;
	v3 = v3_;
	v4 = v4_;
	v5 = v5_;
	v6 = v6_;
	v7 = v7_;
	v8 = v8_;

	refresh();
}
void BoundingBox::translate(int x, int y, int z)
{
	v1.x += x;
	v1.y += y;
	v1.z += z;

	v2.x += x;
	v2.y += y;
	v2.z += z;

	v3.x += x;
	v3.y += y;
	v3.z += z;

	v4.x += x;
	v4.y += y;
	v4.z += z;

	v5.x += x;
	v5.y += y;
	v5.z += z;

	v6.x += x;
	v6.y += y;
	v6.z += z;

	v7.x += x;
	v7.y += y;
	v7.z += z;

	v8.x += x;
	v8.y += y;
	v8.z += z;

	refresh();
}
void BoundingBox::refresh()
{
	//calculate center point
	center.x = (v1.x + v7.x) / 2;
	center.y = (v1.y + v7.y) / 2;
	center.z = (v1.z + v7.z) / 2;

	//calculate lengths from center to each direction X, Y, Z
	yHeight = abs(v1.y - v2.y);
	xWidth  = abs(v4.x - v1.x);
	zDepth  = abs(v5.z - v1.z);

	xRadius = xWidth / 2;
	yRadius = yHeight / 2;
	zRadius = zDepth / 2;

	/* 
		Find the midpoints of each face
			average 2 diagonally verticies to find midpoint

		Average the face midpoint, against the BoundingBox center point
		this yields the length in that direction
	*/

	/*
	EVERYTHING IS COUNTER CLOCKWISE

	v1 v4     v5  v8
	v2 v3     v6  v7
	
		Front Face  = v1 v2 v3 v4
		Back Face   = v5 v6 v7 v8
		Left Face   = v1 v2 v6 v5
		Right Face  = v4 v3 v7 v8
		Bottom Face = v2 v6 v7 v3
		Top Face    = v5 v1 v4 v8

		Front Face Midpoint = v1  vs  v4
		Back Face Midpoint  = v5  vs  v7

	//*/

	/*
			Height = |v1 - v2|
			Width  = |v4 - v1|
			Depth  = |v5 - v1|
	//*/
}