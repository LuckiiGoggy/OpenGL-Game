
#include "CQDemo02.h"


#define DEBUG
//#define DEBUG_SCRIPT


CQDemo02::CQDemo02()
{

}
void CQDemo02::init()
{
	last_ticks = 0;
	delta_t = 0;

	screenW = 400;
	screenH = 400;
	screenD = 400;

	summon0 = true;
	summon1 = false;
	summon2 = false;
	summon3 = false;
	summon4 = false;

	red = glm::vec3(1.0f, 0.0f, 0.0f);
	blue = glm::vec3(0.0f, 0.0f, 1.0f);
	green = glm::vec3(0.0f, 1.0f, 0.0f);
	purple = glm::vec3(1.0f, 0.0f, 1.0f);
	cyan = glm::vec3(0.0f, 1.0f, 1.0f);
	yellow = glm::vec3(1.0f, 1.0f, 0.0f);
	black = glm::vec3(0.0f, 0.0f, 0.0f);

	physicsEngine = PhysicsEngine(screenW, screenH);

	initObjects();
}

void CQDemo02::initObjects()
{
	numOfObjects = 4;

	char* spear_obj_filename = (char*) "../Assets/Models/spear.obj";
	char* bottomFace_obj_filename = (char*) "../Assets/Models/face.obj";
	char* wallCube_obj_filename = (char*) "../Assets/Models/wallCube.obj";
	char* floorCube_obj_filename = (char*) "../Assets/Models/floorCube.obj";
	//char* sonic_obj_filename = (char*) "../Assets/Models/sonic.obj";
	char* v_shader_filename1 = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename1 = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	MeshObject* mesh0 = new MeshObject();
	MeshObject* mesh1 = new MeshObject();
	MeshObject* mesh2 = new MeshObject();
	MeshObject* mesh3 = new MeshObject();

	mesh0->Init(spear_obj_filename, v_shader_filename1, f_shader_filename1);
	mesh1->Init(spear_obj_filename, v_shader_filename1, f_shader_filename1);
	mesh2->Init(floorCube_obj_filename, v_shader_filename1, f_shader_filename1);
	mesh3->Init(spear_obj_filename, v_shader_filename1, f_shader_filename1);
	
	physicsEngine.registerRigidBody(mesh0, "spear0", 1.0f);
	physicsEngine.registerRigidBody(mesh1, "spear1", 1.0f);
	physicsEngine.registerRigidBody(mesh2, "floorCube2", 3.0f);
	physicsEngine.registerRigidBody(mesh3, "spear3", 1.0f);

	physicsEngine.rigidObjects[0]->SetPosition(0, 0, 0);
	physicsEngine.rigidObjects[1]->SetPosition(0, 0, 3);
	physicsEngine.rigidObjects[2]->SetPosition(2, 0, 2);
	physicsEngine.rigidObjects[3]->SetPosition(-1, 0, 1);

	
	for (i = 0; i < numOfObjects; i++)
	{
		physicsEngine.rigidObjects[i]->positionMesh();
	}

	
	
	for (i = 0; i < numOfObjects; i++)
	{
		GlutManager::AddMember(physicsEngine.rigidObjects[i]->GetName(), physicsEngine.rigidObjects[i]);
		//GlutManager::AddMember(physicsEngine.rigidObjects[i]->GetName(), physicsEngine.rigidObjects[i]->pMesh);
	}
	//*/
	

}

void CQDemo02::Update(float timeDelta)
{

}
void CQDemo02::renderSummon()
{
	if (InputManager::isKeyDown('0'))
	{
		summon0 = true;
		summon1 = false;
		summon4 = false;
		summon3 = false;
		summon2 = false;
	}
	if (InputManager::isKeyDown('1'))
	{
		summon1 = true;
		summon0 = false;
		summon4 = false;
		summon3 = false;
		summon2 = false;
	}
	if (InputManager::isKeyDown('2'))
	{
		summon2 = true;
		summon3 = false;
		summon4 = false;
		summon1 = false;
		summon0 = false;
	}
	if (InputManager::isKeyDown('3'))
	{
		summon3 = true;
		summon0 = false;
		summon4 = false;
		summon2 = false;
		summon1 = false;
	}
	if (InputManager::isKeyDown('4'))
	{
		summon4 = true;
		summon3 = false;
		summon2 = false;
		summon1 = false;
		summon0 = false;
	}
	//z+ is into screen
	//z- is out of screen
	//x+ is left
	//x- is right
	//y+ is up
	//y- is down
	if (summon3)
	{
		if (InputManager::isLeftButtonDown())
		{
			Velocity* f3 = new Velocity(3, 0, 0, 3, 10);
			physicsEngine.rigidObjects[3]->addVelocity(f3);
		}
	}
	if (summon2)
	{
		if (InputManager::isLeftButtonDown())
		{
			Velocity* f2 = new Velocity(-3, 0, 0, 3, 10);
			physicsEngine.rigidObjects[2]->addVelocity(f2);
		}
	}
	if (summon1)//spear
	{
		if (InputManager::isLeftButtonDown())
		{
			Velocity* f1 = new Velocity(3, 0, -2, 3, 10);//-2
			physicsEngine.rigidObjects[1]->addVelocity(f1);
		}
	}
	if (summon0)//spear
	{
		if (InputManager::isLeftButtonDown())
		{
			Velocity* f0 = new Velocity(0, 0, 2, 3, 10);//2
			physicsEngine.rigidObjects[0]->addVelocity(f0);
		}
	}
}

void CQDemo02::Render()
{
	delta_t = glutGet(GLUT_ELAPSED_TIME) - last_ticks;
	last_ticks = glutGet(GLUT_ELAPSED_TIME);

	
	//At every frame, you will insert all objects into the quadtree by
	//first clearing the quadtree then using the insert method for every object.
	physicsEngine.updateQuadTree();
	/*
	Once all objects have been inserted,
	you will go through each object and retrieve a
	list of objects it could possibly collide with.
	You'll then check for collisions between each
	object in the list and the initial object,
	using a collision detection algorithm.
	//*/
	physicsEngine.quadTreeCollision();
	//physicsEngine.bruteCollision();

	//Render velocities created on click for debug
	renderSummon();

	//Every frame you must apply all of an objects Velocities, to that object respectively.
	//physicsEngine.updateVelocities(rigidObjects, true);
	physicsEngine.updateVelocities();

	

	

	

	glFlush();
}







//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@ DRAWING FUNCTIONS @@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

void CQDemo02::drawRect(LocationRect r)
{
	//glColor3f(r.color.x, r.color.y, r.color.z);
	glColor3f(r.r, r.g, r.b);
	glBegin(GL_POLYGON);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx, r.sy, screenW, screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx, r.ey, screenW, screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex, r.ey, screenW, screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex, r.sy, screenW, screenH);

	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);
	glVertex3f(v4.x, v4.y, v4.z);

	glEnd();

}
void CQDemo02::drawRect(LocationRect r, glm::vec3 color)
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_POLYGON);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx, r.sy, screenW, screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx, r.ey, screenW, screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex, r.ey, screenW, screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex, r.sy, screenW, screenH);

	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);
	glVertex3f(v4.x, v4.y, v4.z);

	glEnd();

}
void CQDemo02::drawRect(LocationRect r, bool DRAWID)
{
	glColor3f(r.r, r.g, r.b);
	glBegin(GL_POLYGON);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx, r.sy, screenW, screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx, r.ey, screenW, screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex, r.ey, screenW, screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex, r.sy, screenW, screenH);

	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);
	glVertex3f(v4.x, v4.y, v4.z);
	glEnd();

	glColor3f(black.x, black.y, black.z);
	glRasterPos2f(v3.x, v3.y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, r.id_c);

}
void CQDemo02::drawRect(LocationRect r, glm::vec3 color, bool DRAWID)
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_POLYGON);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx, r.sy, screenW, screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx, r.ey, screenW, screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex, r.ey, screenW, screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex, r.sy, screenW, screenH);

	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);
	glVertex3f(v4.x, v4.y, v4.z);
	glEnd();

	glColor3f(black.x, black.y, black.z);
	glRasterPos2f(v3.x, v3.y);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, r.id_c);

}
void CQDemo02::drawRectBounds(LocationRect r)
{
	glColor3f(r.r, r.g, r.b);
	glBegin(GL_LINE_LOOP);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx, r.sy, screenW, screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx, r.ey, screenW, screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex, r.ey, screenW, screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex, r.sy, screenW, screenH);

	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);
	glVertex3f(v4.x, v4.y, v4.z);

	glEnd();

}
void CQDemo02::drawRectBounds(LocationRect r, glm::vec3 color)
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINE_LOOP);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx, r.sy, screenW, screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx, r.ey, screenW, screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex, r.ey, screenW, screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex, r.sy, screenW, screenH);

	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);
	glVertex3f(v4.x, v4.y, v4.z);

	glEnd();

}

glm::vec3 CQDemo02::calcRelativePoints2D(int x, int y, int screenWidth, int screenHeight)
{
	float w = screenWidth / 2;
	float h = screenHeight / 2;

	float newX = (x - w) / w;
	float newY = (y - h) / h;

	glm::vec3 newCord(newX, newY, 0.0f);
	return newCord;
}