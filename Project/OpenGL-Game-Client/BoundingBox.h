
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Math.h"
#include "Dependencies\glm\glm\glm.hpp"

class BoundingBox
{
public:

	BoundingBox();
	BoundingBox(bool SCALE_FROM_1x1x1);
	BoundingBox(bool SCALE_FROM_1x1x1, bool REMAPPED);
	BoundingBox(glm::vec3 v1,
		glm::vec3 v2,
		glm::vec3 v3,
		glm::vec3 v4,
		glm::vec3 v5,
		glm::vec3 v6,
		glm::vec3 v7,
		glm::vec3 v8);

	void refresh();
	void translate(int x, int y, int z);
	void translate(float x, float y, float z);

	float* returnFrontFaceXY();
	float* returnLeftFaceYZ();
	float* returnBottomFaceXZ();
	//returns an array of 8 floats, 
	//[0] = V1.x [1] = V1.z
	//[2] = V2.x [3] = V2.z
	//in counter clockwise ordering

	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 v4;
	glm::vec3 v5;
	glm::vec3 v6;
	glm::vec3 v7;
	glm::vec3 v8;

	glm::vec3 center;

	float yHeight;
	float xWidth;
	float zDepth;

	float xRadius;
	float yRadius;
	float zRadius;

	float MinVertex(float, float, float, float);
	float MaxVertex(float, float, float, float);
};


#endif