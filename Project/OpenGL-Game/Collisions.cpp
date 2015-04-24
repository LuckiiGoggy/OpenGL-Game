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

/*
public class SelectionMath
{
    

    SelectionMath(){
    }
    SelectionMath(int radiusGiven){
        radius = radiusGiven;
    }
    public void setRadius(int radiusGiven){
        radius = radiusGiven;
    }
    
    public int checkForSelect(int mousePointX,
                              int mousePointY,
                              int shapePointSX,
                              int shapePointSY,
                              int shapePointEX,
                              int shapePointEY) {
        int i;
        float centerX = (shapePointSX + shapePointEX) / 2;
        float centerY = (shapePointSY + shapePointEY) / 2;

        if ( Math.abs( mousePointX - shapePointSX)  <= radius )
        {
            if ( Math.abs( mousePointY - shapePointSY)  <= radius )
            {
                return STARTPOINTS;
            }
        }
        if ( Math.abs( mousePointX - shapePointEX)  <= radius )
        {
            if ( Math.abs( mousePointY - shapePointEY)  <= radius )
            {
                return ENDPOINTS;
            }
        }
        for (i = (-radius); i <= radius; i++) {
            //first point in line
            if ((mousePointX + i) == shapePointSX)//check X within radius
            {
                for (i = (-radius); i <= radius; i++)//check Y within radius
                {
                    if ((mousePointY + i) == shapePointSY) {
                        return STARTPOINTS;
                    }
                }
            }
            //second point in line
            if ((mousePointX + i) == shapePointEX)//check X within radius
            {
                for (i = (-radius); i <= radius; i++)//check Y within radius
                {
                    if ((mousePointY + i) == shapePointEY) {
                        return ENDPOINTS;
                    }
                }
            }
            //center point in line
            if ((mousePointX + i) == (int)centerX)//check X within radius
            {
                for (i = (-radius); i <= radius; i++)//check Y within radius
                {
                    if ((mousePointY + i) == (int)centerY) {
                        return CENTERPOINT;
                    }
                }
            }
        }

        return 0;
    }
    public int checkForSelect(PointF mousePoint, PointF[] shapePoints) {
        int i;
        PointF center = new PointF();
        center.x = (shapePoints[0].x + shapePoints[1].x) / 2;
        center.y = (shapePoints[0].y + shapePoints[1].y) / 2;

        /*boolean horizontal = false;
        boolean vertical = false;
        if (Math.abs(shapePoints[0].x - shapePoints[1].x) <= VERTRANGE)
        {
            vertical = true;
        }
        if (Math.abs(shapePoints[0].y - shapePoints[1].y) <= HORIZRANGE)
        {
            horizontal = true;
        }*//*

        if ( Math.abs( (int)mousePoint.x - shapePoints[0].x)  <= radius )
        {
            if ( Math.abs( (int)mousePoint.y - shapePoints[0].y)  <= radius )
            {
                return STARTPOINTS;
            }
        }
        if ( Math.abs( (int)mousePoint.x - shapePoints[1].x)  <= radius )
        {
            if ( Math.abs( (int)mousePoint.y - shapePoints[1].y)  <= radius )
            {
                return ENDPOINTS;
            }
        }
        for (i = (-radius); i <= radius; i++) {
            //first point in line
            if (((int)mousePoint.x + i) == (int)shapePoints[0].x)//check X within radius
            {
                for (i = (-radius); i <= radius; i++)//check Y within radius
                {
                    if ((int)(mousePoint.y + i) == (int)shapePoints[0].y) {
                        return STARTPOINTS;
                    }
                }
            }
            //second point in line
            if ((int)(mousePoint.x + i) == (int)shapePoints[1].x)//check X within radius
            {
                for (i = (-radius); i <= radius; i++)//check Y within radius
                {
                    if ((int)(mousePoint.y + i) == (int)shapePoints[1].y) {
                        return ENDPOINTS;
                    }
                }
            }
            //center point in line
            if ((int)(mousePoint.x + i) == (int)center.x)//check X within radius
            {
                for (i = (-radius); i <= radius; i++)//check Y within radius
                {
                    if ((int)(mousePoint.y + i) == (int)center.y) {
                        return CENTERPOINT;
                    }
                }
            }
        }

        return 0;
    }

}


*/