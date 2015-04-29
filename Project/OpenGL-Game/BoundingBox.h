
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Math.h"
#include "Dependencies\glm\glm\glm.hpp";

class BoundingBox
{
public:

	BoundingBox();
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
	

	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 v4;
	glm::vec3 v5;
	glm::vec3 v6;
	glm::vec3 v7;
	glm::vec3 v8;

	glm::vec3 center;

	int yHeight;
	int xWidth;
	int zDepth;

	int xRadius;
	int yRadius;
	int zRadius;

	int xMid;
	int yMid;
	int zMid;

};


#endif