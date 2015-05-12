
#include "BoundingBox.h"
#include <math.h>
#include <cfloat>

float* BoundingBox::returnFrontFaceXY()
{
	//Bottom Face = v2 v6 v7 v3
	/*
	v1      v4          Y
	^
	v2      v3      X<__|    Z points into Front Face
	*/
	float* vertices = new float[8];
	vertices[0] = v1.x;      vertices[6] = v4.x;
	vertices[1] = v1.y;      vertices[7] = v4.y;

	vertices[2] = v2.x;      vertices[4] = v3.x;
	vertices[3] = v2.y;      vertices[5] = v3.y;

	return vertices;
}
float* BoundingBox::returnBottomFaceXZ()
{
	//Bottom Face = v2 v6 v7 v3
	/*
	v6      v7          Z
	^
	v2      v3      X<__|    Y points out of Bottom Face
	*/
	float* vertices = new float[8];
	vertices[0] = v6.x;      vertices[6] = v7.x;
	vertices[1] = v6.z;      vertices[7] = v7.z;

	vertices[2] = v2.x;      vertices[4] = v3.x;
	vertices[3] = v2.z;      vertices[5] = v3.z;

	return vertices;
}
float* BoundingBox::returnLeftFaceYZ()
{
	//Left Face   = v1 v2 v6 v5
	/*
	v5      v1          Y
	^
	v6      v2      Z<__|     X points out of Left Face
	*/
	float* vertices = new float[8];
	vertices[0] = v5.y;      vertices[6] = v1.y;
	vertices[1] = v5.z;      vertices[7] = v1.z;

	vertices[2] = v6.y;      vertices[4] = v2.y;
	vertices[3] = v6.z;      vertices[5] = v2.z;

	return vertices;
}

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
BoundingBox::BoundingBox(bool SCALE_FROM_1x1x1)
{
	//Creates a bounding box with lengths of 1
	v1 = glm::vec3(-0.5f, -0.5f, -0.5f);
	v2 = glm::vec3(0.5f, -0.5f, -0.5f);
	v3 = glm::vec3(0.5f, 0.5f, -0.5f);
	v4 = glm::vec3(-0.5f, 0.5f, -0.5f);
	v5 = glm::vec3(-0.5f, -0.5f, 0.5f);
	v6 = glm::vec3(0.5f, -0.5f, 0.5f);
	v7 = glm::vec3(0.5f, 0.5f, 0.5f);
	v8 = glm::vec3(-0.5f, 0.5f, 0.5f);

	refresh();
}
BoundingBox::BoundingBox(bool SCALE_FROM_1x1x1, bool REMAPPED)
{
	//Creates a bounding box with lengths of 1
	v1 = glm::vec3(-0.5f, 0.5f, -0.5f);
	v2 = glm::vec3(-0.5f, -0.5f, -0.5f);
	v3 = glm::vec3(0.5f, -0.5f, -0.5f);
	v4 = glm::vec3(0.5f, 0.5f, -0.5f);
	v5 = glm::vec3(-0.5f, 0.5f, 0.5f);
	v6 = glm::vec3(-0.5f, -0.5f, 0.5f);
	v7 = glm::vec3(0.5f, -0.5f, 0.5f);
	v8 = glm::vec3(0.5f, 0.5f, 0.5f);

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
void BoundingBox::translate(float x, float y, float z)
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
	yHeight = abs(v1.y - v6.y);
	//xWidth = abs(MinVertex(v5.x, v1.x, v4.x, v8.x) - MaxVertex(v5.x, v1.x, v4.x, v8.x));
	//zDepth = abs(MinVertex(v5.z, v1.z, v4.z, v8.z) - MaxVertex(v5.z, v1.z, v4.z, v8.z));

	xWidth = abs(v5.x - v4.x);
	zDepth = abs(v5.z - v4.z);

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

float BoundingBox::MinVertex(float v1, float v2, float v3, float v4)
{
	float vertices[4] = { v1, v2, v3, v4 };
	float min = FLT_MAX;

	for (int i = 0; i < 4; i++){
		if (vertices[i] < min) min = vertices[i];
	}

	return min;
}

float BoundingBox::MaxVertex(float v1, float v2, float v3, float v4)
{
	float vertices[4] = { v1, v2, v3, v4 };
	float max = -FLT_MAX;

	for (int i = 0; i < 4; i++){
		if (vertices[i] > max) max = vertices[i];
	}

	return max;
}
