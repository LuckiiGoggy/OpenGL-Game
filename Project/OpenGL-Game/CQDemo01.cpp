
#include "CQDemo01.h"

CQDemo01::CQDemo01()
{

}
void CQDemo01::init()
{
	numOfObjects = 10;

	screenW = 400;
	screenH = 400;

	red = glm::vec3(1.0f, 0.0f, 0.0f);
	blue = glm::vec3(0.0f, 0.0f, 1.0f);
	green = glm::vec3(0.0f, 1.0f, 0.0f);
	purple = glm::vec3(1.0f, 0.0f, 1.0f);
	cyan = glm::vec3(0.0f, 1.0f, 1.0f);
	yellow = glm::vec3(1.0f, 1.0f, 0.0f);
	black = glm::vec3(0.0f, 0.0f, 0.0f);
	
	objects[0] = Rect(20,20,40,40, blue);
	objects[1] = Rect(120, 20, 140, 40, cyan);
	objects[2] = Rect(50,50, 70, 70, purple);
	objects[3] = Rect(150, 50, 170, 70, red);

	for (int i = 5; i < 11; i++)
	{

		objects[i] = Rect(50 + (23 * i),50 + (23 * i), 70+ (23 * i), 70+ (23 * i), green);
	}
	

	quad = Quadtree(0, Rect(0,0, screenW, screenH));
}
void CQDemo01::renderDemo1()
{
	moveObjects();
	/* 

	At every frame, you’ll insert all objects into the quadtree by 
	first clearing the quadtree then using the insert method for every object.

	//*/
	
	quad.clear();
	for (i = 0; i < numOfObjects; i++) {
		quad.insert(objects[i]);
	}//*/

	/* 

	Once all objects have been inserted, 
	you will go through each object and retrieve a
	list of objects it could possibly collide with.
	You'll then check for collisions between each
	object in the list and the initial object, 
	using a collision detection algorithm.
	
	//*/

	list<Rect> returnObjects = list<Rect>();

	for (i = 0; i < numOfObjects; i++) {

		returnObjects.clear();
		quad.retrieve(&returnObjects, objects[i]);

		for (int x = 0; x < returnObjects.size(); x++) {
			// Run collision detection algorithm between objects
		}
	}//*/

	for (i = 0; i < numOfObjects; i++)
	{
		drawRect(objects[i]);
	}

	//draw the actual split up collision relavence tree
	quad.draw();

	glFlush();
}
void CQDemo01::moveObjects()
{
	objects[0].sx++;
	objects[0].ex++;

	objects[1].sx--;
	objects[1].ex--;
}
void CQDemo01::beginDemo()
{

}

void CQDemo01::drawRect(Rect r)
{
	glColor3f(r.color.x, r.color.y, r.color.z);
	glBegin(GL_POLYGON);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx,r.sy,screenW,screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx,r.ey,screenW,screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex,r.ey,screenW,screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex,r.sy,screenW,screenH);

	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v3.x,v3.y,v3.z);
	glVertex3f(v4.x,v4.y,v4.z);

	glEnd();

}
void CQDemo01::drawRect(Rect r, glm::vec3 color)
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_POLYGON);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx,r.sy,screenW,screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx,r.ey,screenW,screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex,r.ey,screenW,screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex,r.sy,screenW,screenH);

	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v3.x,v3.y,v3.z);
	glVertex3f(v4.x,v4.y,v4.z);

	glEnd();

}
void CQDemo01::drawRectBounds(Rect r, glm::vec3 color)
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINE_LOOP);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx,r.sy,screenW,screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx,r.ey,screenW,screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex,r.ey,screenW,screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex,r.sy,screenW,screenH);

	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v3.x,v3.y,v3.z);
	glVertex3f(v4.x,v4.y,v4.z);

	glEnd();

}
glm::vec3 CQDemo01::calcRelativePoints2D(int x, int y, int screenWidth, int screenHeight)
{
	float w = screenWidth / 2;
	float h = screenHeight / 2;

	float newX = (x - w) / w;
	float newY = (y - h) / h;

	glm::vec3 newCord(newX, newY, 0.0f);
	return newCord;
}
