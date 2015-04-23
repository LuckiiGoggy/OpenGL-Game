

#ifndef COLLISIONS_H
#define COLLISIONS_H


class Collisions
{
public:
	Collisions();
	~Collisions();
	int checkForSelect(float mousePointX,
		float mousePointY,
		float shapePointSX,
		float shapePointSY,
		float shapePointEX,
		float shapePointEY);

	int ENDPOINTS;
	int STARTPOINTS;
	int CENTERPOINT;

	int radius;

};

#endif