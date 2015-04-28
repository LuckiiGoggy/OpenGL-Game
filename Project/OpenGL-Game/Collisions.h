

#ifndef COLLISIONS_H
#define COLLISIONS_H


class Collisions
{
public:
	Collisions();
	~Collisions();

	//Axis Aligned Bounding Box
	bool checkCollisionAAB(int aX, int aY, int aZ, int aXsize, int aYsize, int aZsize,
		int bX, int bY, int bZ, int bXsize, int bYsize, int bZsize);

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