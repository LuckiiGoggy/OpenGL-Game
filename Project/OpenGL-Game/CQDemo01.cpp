
#include "CQDemo01.h"


#define DEBUG
//#define DEBUG_SCRIPT

CQDemo01::CQDemo01()
{
	rectObjects = std::vector<RectObject*>();
}
void CQDemo01::init()
{
	last_ticks = 0;
	delta_t = 0;

	screenW = 400;
	screenH = 400;

	timerDelay = 5;
	timerDelayCounter = timerDelay;

	red = glm::vec3(1.0f, 0.0f, 0.0f);
	blue = glm::vec3(0.0f, 0.0f, 1.0f);
	green = glm::vec3(0.0f, 1.0f, 0.0f);
	purple = glm::vec3(1.0f, 0.0f, 1.0f);
	cyan = glm::vec3(0.0f, 1.0f, 1.0f);
	yellow = glm::vec3(1.0f, 1.0f, 0.0f);
	black = glm::vec3(0.0f, 0.0f, 0.0f);

	pause = false;
	summon9 = true;
	summon0 = false;
	summon1 = false;
	summon3 = false;

	//______________________________________________
	initObjects();
	quad = Quadtree(0, Rect(0,0, screenW, screenH));

	collision = Collisions();
	physicsEngine = PhysicsEngine(screenW, screenH);
}
void CQDemo01::initObjects()
{
	numOfObjects = 10;

	//objects[0] = Rect(20,20,40,40, blue, 0);
	//objects[1] = Rect(120, 20, 140, 40, cyan, 1);
	//objects[2] = Rect(50,50, 70, 70, purple, 2);
	//objects[3] = Rect(152, 50, 172, 70, red, 3);

	//rectObjects[0] = new RectObject(20,20,40,40, blue, 0);
	//rectObjects[1] = new RectObject(120, 20, 140, 40, cyan, 1);
	//rectObjects[2] = new RectObject(50,50, 70, 70, purple, 2);
	//rectObjects[3] = new RectObject(152, 50, 172, 70, red, 3);
	rectObjects.push_back(new RectObject(20,20,40,40, blue, 0));
	rectObjects.push_back(new RectObject(120, 20, 140, 40, cyan, 1));
	rectObjects.push_back(new RectObject(50,50, 70, 70, purple, 2));
	rectObjects.push_back(new RectObject(152, 50, 172, 70, red, 3));


	for (int i = 4; i < numOfObjects; i++)
	{
		//objects[i] = Rect(50 + (23 * i),50 + (23 * i), 70+ (23 * i), 70+ (23 * i), green, i);
		//rectObjects[i] = new RectObject(50 + (23 * i),50 + (23 * i), 70+ (23 * i), 70+ (23 * i), green, i);
		rectObjects.push_back(new RectObject(50 + (23 * i),50 + (23 * i), 70+ (23 * i), 70+ (23 * i), green, i));
	}
	/*
	for (int i = 0; i < numOfObjects; i++)
	{
		rectObjects.push_back(new RectObject(objects[i]));
	}//*/

	Velocity* f0 = new Velocity(4, 0, 0, 1, 100);
	rectObjects[0]->addVelocity(f0);

	Velocity* f1 = new Velocity(-3, 0, 0, 1, 100);
	rectObjects[1]->addVelocity(f1);

	Velocity* f8 = new Velocity(0, -3, 0, 1, 100);
	rectObjects[8]->addVelocity(f8);

	Velocity* f3 = new Velocity(0, 3, 0, 1, 100);
	rectObjects[3]->addVelocity(f3);

	Velocity* f4 = new Velocity(0, -3, 0, 1, 100);
	rectObjects[4]->addVelocity(f4);

}
void CQDemo01::renderSummon()
{
	if (InputManager::isKeyDown('9'))
	{
		summon9 = true;
		summon0 = false;
		summon1 = false;
		summon3 = false;
	}
	if (InputManager::isKeyDown('0'))
	{
		summon0 = true;
		summon9 = false;
		summon1 = false;
		summon3 = false;
	}
	if (InputManager::isKeyDown('1'))
	{
		summon1 = true;
		summon0 = false;
		summon9 = false;
		summon3 = false;
	}
	if (InputManager::isKeyDown('3'))
	{
		summon3 = true;
		summon0 = false;
		summon9 = false;
		summon1 = false;
	}
	if (summon9)
	{
		if(InputManager::isLeftButtonDown())
		{
			int mx = InputManager::GetMousePos().x;
			int my = InputManager::GetMousePos().y;
			//objects[9] = Rect(mx, my, mx + 20, my + 20, yellow, 9);	
			//rectObjects[9] = new RectObject(objects[9]);
			rectObjects[9] = new RectObject(mx, my, mx + 40, my + 40, yellow, 9);
			rectObjects[9]->mass = 2;
			Velocity* f9 = new Velocity(0, -3, 0, 1, 100);
			rectObjects[9]->addVelocity(f9);
		}
	}
	if (summon0)
	{
		if(InputManager::isLeftButtonDown())
		{
			int mx = InputManager::GetMousePos().x;
			int my = InputManager::GetMousePos().y;
			//objects[9] = Rect(mx, my, mx + 20, my + 20, yellow, 9);	
			//rectObjects[9] = new RectObject(objects[9]);
			rectObjects[0] = new RectObject(mx, my, mx + 20, my + 20, blue, 0);
			rectObjects[0]->mass = 1;
			Velocity* f0= new Velocity(4, 0, 0, 1, 100);
			rectObjects[0]->addVelocity(f0);
		}
	}
	if (summon1)
	{
		if(InputManager::isLeftButtonDown())
		{
			int mx = InputManager::GetMousePos().x;
			int my = InputManager::GetMousePos().y;
			//objects[9] = Rect(mx, my, mx + 20, my + 20, yellow, 9);	
			//rectObjects[9] = new RectObject(objects[9]);
			rectObjects[1] = new RectObject(mx, my, mx + 20, my + 20, cyan, 1);
			rectObjects[1]->mass = 1;
			Velocity* f1 = new Velocity(-4, 0, 0, 1, 100);
			rectObjects[1]->addVelocity(f1);
		}
	}
	if (summon3)
	{
		if(InputManager::isLeftButtonDown())
		{
			int mx = InputManager::GetMousePos().x;
			int my = InputManager::GetMousePos().y;
			//objects[9] = Rect(mx, my, mx + 20, my + 20, yellow, 9);	
			//rectObjects[9] = new RectObject(objects[9]);
			rectObjects[3] = new RectObject(mx, my, mx + 20, my + 20, red, 3);
			rectObjects[3]->mass = 1;
			Velocity* f3 = new Velocity(0, 3, 0, 1, 100);
			rectObjects[3]->addVelocity(f3);
		}
	}
}
void CQDemo01::renderDemo1()
{
	delta_t = glutGet(GLUT_ELAPSED_TIME) - last_ticks;
	last_ticks = glutGet(GLUT_ELAPSED_TIME);

	#ifdef DEBUG_SCRIPT
		if(InputManager::isRightButtonDown()){
			if (pause){pause = false;}
			else{pause = true;}}
		if (pause){return;}
	#endif

	//Render objects created on click for debug
	renderSummon();

	//               DRAWING

	for (i = 0; i < numOfObjects; i++)
	{
		drawRect(*rectObjects[i]);
	}
	
	/* 
		Every frame you must apply all of an objects Velocities,
		to that object respectively.
	*/
	physicsEngine.updateVelocities(rectObjects);
	
	/* 
	At every frame, you will insert all objects into the quadtree by 
	first clearing the quadtree then using the insert method for every object.
	//*/
	
	//quad = Quadtree(0, Rect(0,0, screenW, screenH));
	quad.clear();
	for (i = 0; i < numOfObjects; i++) {
		//quad.insert(&objects[i]);
		quad.insert(rectObjects[i]);
	}//*/

	/* 
	Once all objects have been inserted, 
	you will go through each object and retrieve a
	list of objects it could possibly collide with.
	You'll then check for collisions between each
	object in the list and the initial object, 
	using a collision detection algorithm.
	//*/

	//list<Rect*> returnObjects = list<Rect*>();
	list<RectObject*> returnObjects = list<RectObject*>();

	for (i = 0; i < numOfObjects; i++) {

		returnObjects.clear();
		//quad.retrieve(&returnObjects, &objects[i]);
		quad.retrieve(&returnObjects, rectObjects[i]);

		#ifdef DEBUG_SCRIPT
			cout << "\n object:" << objects[i].id_c << " vs";
		#endif

		/*
		for (int x = 0; x < returnObjects.size(); x++) {
			// Run collision detection algorithm between objects
		}//*/
		for ( list<RectObject*>::iterator it = returnObjects.begin(); it != returnObjects.end(); ++it)
		{
			//Rect* cur = *it;
			RectObject* cur = *it;
			#ifdef DEBUG_SCRIPT
				cout << "\n object:" << cur->id_c;
			#endif

			if (cur->id != rectObjects[i]->id)//if (cur->id != objects[i].id)
			{
				/*bool hit = collision.checkCollisionAAB(cur->Bbox.center.x, cur->Bbox.center.y, cur->Bbox.center.z,
					cur->Bbox.xRadius, cur->Bbox.yRadius, cur->Bbox.zRadius,
					objects[i].Bbox.center.x, objects[i].Bbox.center.y, objects[i].Bbox.center.z,
					objects[i].Bbox.xRadius, objects[i].Bbox.yRadius, objects[i].Bbox.zRadius);//*/
				bool hit = collision.checkCollisionAAB(cur->Bbox.center.x, cur->Bbox.center.y, cur->Bbox.center.z,
					cur->Bbox.xRadius, cur->Bbox.yRadius, cur->Bbox.zRadius,
					rectObjects[i]->Bbox.center.x, rectObjects[i]->Bbox.center.y, rectObjects[i]->Bbox.center.z,
					rectObjects[i]->Bbox.xRadius, rectObjects[i]->Bbox.yRadius, rectObjects[i]->Bbox.zRadius);
				if (hit)
				{
					//cout << "\n HIT " << objects[i].id_c << " vs " << cur->id_c;
					cout << "\n HIT " << rectObjects[i]->id_c << " vs " << cur->id_c;
					physicsEngine.triggerImpact(cur, rectObjects[i]);
				}
			}
			
		}
	}//*/


	//               DRAWING

	for (i = 0; i < numOfObjects; i++)
	{
		#ifdef DEBUG
			//drawRect(objects[i], true);
			drawRect(*rectObjects[i], true);
		#endif
		#ifndef DEBUG
			//drawRect(objects[i]);
			drawRect(*rectObjects[i]);
		#endif
	}

	//draw the quad tree regions
	#ifdef DEBUG
		quad.draw(true); //draw(true) labels which elements are contained in each node
	#endif
	#ifndef DEBUG
		quad.draw(); 
	#endif
	

	glFlush();
}
void CQDemo01::moveObjects()
{
	//objects[0].move(1,0);
	//rectObjects[0]->move(1,0);

	//objects[1].move(-1,0);
	//rectObjects[1]->move(-1,0);

	//objects[8].move(0, -1);
	//rectObjects[8]->move(0,-1);

	//objects[9].move(0, -1);
	//rectObjects[9]->move(0,-1);

	//objects[3].move(0, 1);
	//rectObjects[3]->move(0,1);
}

void CQDemo01::drawRect(Rect r)
{
	//glColor3f(r.color.x, r.color.y, r.color.z);
	glColor3f(r.r, r.g, r.b);
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
void CQDemo01::drawRect(Rect r, bool DRAWID)
{
	glColor3f(r.r, r.g, r.b);
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

	glColor3f(black.x, black.y, black.z);
	glRasterPos2f(v3.x, v3.y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, r.id_c );

}
void CQDemo01::drawRect(Rect r, glm::vec3 color, bool DRAWID)
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

	glColor3f(black.x, black.y, black.z);
	glRasterPos2f(v3.x, v3.y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, r.id_c );

}
void CQDemo01::drawRectBounds(Rect r)
{
	glColor3f(r.r, r.g, r.b);
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
	float newY = (h - y) / h;

	glm::vec3 newCord(newX, newY, 0.0f);
	return newCord;
}
