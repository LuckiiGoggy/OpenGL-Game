#include "Collisions.h"
#include "Math.h"

Collisions::Collisions()
{
	ENDPOINTS = 11;
	STARTPOINTS = 22;
	CENTERPOINT = 33;

	radius = 40;
}
Collisions::~Collisions()
{
}
//*
/* 
	aX, aY aZ are the center points x,y,z respectively for bounding box 'A'
	aXsize is the length from the center X point to the outside edge of the box
	aYsize is the length from the center Y point to the outside edge of the box
	aZsize is the length from the center Z point to the outside edge of the box
*/
bool Collisions::checkCollisionAAB(int aX, int aY, int aZ, int aXsize, int aYsize, int aZsize,
								int bX, int bY, int bZ, int bXsize, int bYsize, int bZsize)
{
	{
		//check the Y axis
		if(abs(aY - bY) < aYsize + bYsize)
		{
			//check the X axis
			if(abs(aX - bX) < aXsize + bXsize)
			{
				//check the Z axis
				if(abs(aZ - bZ) < aZsize + bZsize)
				{
					return true;
				}
			}
		}

		return false;
	} 
}//*/
/*
bool Collisions::checkCollisionAAB(ObjectBox a, ObjectBox b)
{
	{
		//check the Y axis
		if(abs(a.getY() - b.getY()) < a.getSizeY() + b.getSizeY())
		{
			//check the X axis
			if(abs(a.getX() - b.getX()) < a.getSizeX() + b.getSizeX())
			{
				//check the Z axis
				if(abs(a.getZ() - b.getZ()) < a.getSizeZ() + b.getSizeZ())
				{
					return true;
				}
			}
		}

		return false;
	} 
}//*/
int Collisions::checkForSelect(float mousePointX,
							   float mousePointY,
							   float shapePointSX,
							   float shapePointSY,
							   float shapePointEX,
							   float shapePointEY) {

							  int i;
							  float centerX = (shapePointSX + shapePointEX) / 2;
							  float centerY = (shapePointSY + shapePointEY) / 2;

							  if ( abs( (int)mousePointX - shapePointSX)  <= radius )
							  {
								  if ( abs( (int)mousePointY - shapePointSY)  <= radius )
								  {
									  return STARTPOINTS;
								  }
							  }
							  if ( abs( (int)mousePointX - shapePointEX)  <= radius )
							  {
								  if ( abs( (int)mousePointY - shapePointEY)  <= radius )
								  {
									  return ENDPOINTS;
								  }
							  }
							  for (i = (-radius); i <= radius; i++) {
								  //first point in line
								  if (((int)mousePointX + i) == (int)shapePointSX)//check X within radius
								  {
									  for (i = (-radius); i <= radius; i++)//check Y within radius
									  {
										  if ((int)(mousePointY + i) == (int)shapePointSY) {
											  return STARTPOINTS;
										  }
									  }
								  }
								  //second point in line
								  if ((int)(mousePointX + i) == (int)shapePointEX)//check X within radius
								  {
									  for (i = (-radius); i <= radius; i++)//check Y within radius
									  {
										  if ((int)(mousePointY + i) == (int)shapePointEY) {
											  return ENDPOINTS;
										  }
									  }
								  }
								  //center point in line
								  if ((int)(mousePointX + i) == (int)centerX)//check X within radius
								  {
									  for (i = (-radius); i <= radius; i++)//check Y within radius
									  {
										  if ((int)(mousePointY + i) == (int)centerY) {
											  return CENTERPOINT;
										  }
									  }
								  }
							  }

							  return 0;
}


