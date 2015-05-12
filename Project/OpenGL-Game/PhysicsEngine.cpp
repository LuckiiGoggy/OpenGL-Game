
#include "PhysicsEngine.h"

//#define DEBUG_SCRIPT
#define DEBUG_SCRIPT_DISPLACEMENT
#define PRINT_COLLISION

PhysicsEngine::PhysicsEngine()
{
	screenWidth = 400;
	screenHeight = 400;
	screenDepth = 400;

	collisions = Collisions();
	quadtree = Quadtree(0, Rect(0, 0, screenWidth, screenHeight));
	rigidObjects = vector<RigidBody*>();
}
PhysicsEngine::PhysicsEngine(int screenWidth_, int screenHeight_)
{
	screenWidth = screenWidth_;
	screenHeight = screenHeight_;
	screenDepth = screenHeight_;

	collisions = Collisions();
	quadtree = Quadtree(0, Rect(0, 0, screenWidth, screenHeight));
	rigidObjects = vector<RigidBody*>();
}
PhysicsEngine::PhysicsEngine(int screenWidth_, int screenHeight_, int screenDepth_)
{
	screenWidth = screenWidth_;
	screenHeight = screenHeight_;
	screenDepth = screenDepth_;

	collisions = Collisions();
	quadtree = Quadtree(0, Rect(0, 0, screenWidth, screenHeight));
	rigidObjects = vector<RigidBody*>();
}


///NOT IN USE
void PhysicsEngine::applyVelocity(RectObject* object, Velocity f)
{
	object->move(
		(int)((f.strength) * (f.x)),
		(int)((f.strength) * (f.y))
		);
}
void PhysicsEngine::applyVelocity(RectObject* object, Velocity* f)
{
	object->move(
		(int)((f->strength) * (f->x)),
		(int)((f->strength) * (f->y))
		);
}
void PhysicsEngine::applyVelocity(RectObject* object, float x_, float y_, float z_, int type_, int duration_ /* = 10 */)
{
	Velocity* f = new Velocity(x_, y_, z_, type_, duration_);
	object->addVelocity(f);
	object->move(
		(int)((f->strength) * (f->x)),
		(int)((f->strength) * (f->y))
		);
}
///NOT IN USE




void PhysicsEngine::triggerImpact(RigidBody* A, RigidBody* B)
{
	int numOfVelocities_A = A->velocities.size();
	int numOfVelocities_B = B->velocities.size();

	float xTotal_A = 0;//total x influence (total velocity in the x direction) for object A
	float yTotal_A = 0;//total y influence for object A
	float zTotal_A = 0;//total z influence for object A

	float xTotal_B = 0;//total x influence for object B
	float yTotal_B = 0;//total y influence for object B
	float zTotal_B = 0;//total z influence for object B

	float xImpact_A = 0;//resulting x impact influence created from object A
	float yImpact_A = 0;//resulting y impact influence created from object A
	float zImpact_A = 0;//resulting z impact influence created from object A

	float xImpact_B = 0;//resulting x impact influence created from object B
	float yImpact_B = 0;//resulting y impact influence created from object B
	float zImpact_B = 0;//resulting z impact influence created from object B

	//Sum all of the velocities to get the total influence for object A
	for (int i = 0; i < numOfVelocities_A; i++)
	{
		if (A->velocities[i]->timeLeft > 0)
		{
			xTotal_A += A->velocities[i]->x;
			yTotal_A += A->velocities[i]->y;
			zTotal_A += A->velocities[i]->z;
		}
	}
	//Sum all of the velocities to get the total influence for object B
	for (int i = 0; i < numOfVelocities_B; i++)
	{
		if (B->velocities[i]->timeLeft > 0)
		{
			xTotal_B += B->velocities[i]->x;
			yTotal_B += B->velocities[i]->y;
			zTotal_B += B->velocities[i]->z;
		}
	}

	//Impact = velocity * mass
	xImpact_A = xTotal_A * A->mass; //PA
	yImpact_A = yTotal_A * A->mass;
	zImpact_A = zTotal_A * A->mass;

	xImpact_B = xTotal_B * B->mass; //PB
	yImpact_B = yTotal_B * B->mass;
	zImpact_B = zTotal_B * B->mass;

	//        PA              +          PB             =                  PAB
	//(A->mass * A->Velocity) + (B->mass * B->Velocity) = (A->mass + B->mass)(A->Velocity + B->Velocity)
	//  Velocity AB = (PA + PB) / (mass A + mass B)

	float totalMass = A->mass + B->mass;//PAB mass

	float xImpact_Total = (xImpact_A + xImpact_B);
	float yImpact_Total = (yImpact_A + yImpact_B);
	float zImpact_Total = (zImpact_A + zImpact_B);

	/*
	xImpact_A = xImpact_Total / A->mass;
	yImpact_A = yImpact_Total / A->mass;
	zImpact_A = zImpact_Total / A->mass;

	xImpact_B = xImpact_Total / B->mass;
	yImpact_B = yImpact_Total / B->mass;
	zImpact_B = zImpact_Total / B->mass;//*/


	//resulting velocities from collision
	Velocity* impact_From_A = new Velocity(xImpact_A, yImpact_A, zImpact_A, 3, 10);
	Velocity* impact_From_B = new Velocity(xImpact_B, yImpact_B, zImpact_B, 3, 10);

	//Get how much they overlap by, divide by the sum of the velocities
	//Multiply by velocities of A to get how much A needs to be moved back
	/*
	AreaOfIntersection = Max(0, Max(this.UpRt.x, other.UpRt.x)  - Min(this.LowLt.x, other.LowLt.x)) *
	Max(0, Max(this.UpRt.y, other.UpRt.y) - Min(this.LowLt.y, other.LowLt.y))

	AreaOfOverlap = AreaOfObjectA + AreaOfObjectB - AreaOfIntersection
	*/

	float* bottomFace_A = A->pMesh->boundingBox.returnBottomFaceXZ();
	float* bottomFace_B = B->pMesh->boundingBox.returnBottomFaceXZ();
	float* leftFace_A = A->pMesh->boundingBox.returnLeftFaceYZ();
	float* leftFace_B = B->pMesh->boundingBox.returnLeftFaceYZ();

	// in terms of sx and ex, startX and endX, 
	// start refers to top left and end refers to bottom right
	//sx,sy_____         Y
	//	   |\  |         ^
	//	   | \ |         |__>X
	//	   ==== ex,ey

	//*
	float Asx = A->pMesh->bottomFace.sx;
	float Asz = A->pMesh->bottomFace.sy;
	float Aex = A->pMesh->bottomFace.ex;
	float Aez = A->pMesh->bottomFace.ey;
	float Bsx = B->pMesh->bottomFace.sx;
	float Bsz = B->pMesh->bottomFace.sy;
	float Bex = B->pMesh->bottomFace.ex;
	float Bez = B->pMesh->bottomFace.ey;//*/

	float Asy = leftFace_A[0];
	float Aey = leftFace_A[4];
	float Bsy = leftFace_B[0];
	float Bey = leftFace_B[4];

	float xIntersect = std::fmax(0, (std::fmax(Aex, Bex) - std::fmin(Asx, Bsx)));
	float yIntersect = std::fmax(0, (std::fmax(Aey, Bey) - std::fmin(Asy, Bsy)));
	float zIntersect = std::fmax(0, (std::fmax(Aez, Bez) - std::fmin(Asz, Bsz)));

	float xOverlap = abs((Aex - Asx) + (Bex - Bsx) - xIntersect) / 2;
	float yOverlap = abs((Aey - Asy) + (Bey - Bsy) - yIntersect) / 2;
	float zOverlap = abs((Aez - Asz) + (Bez - Bsz) - zIntersect) / 2;



	/*
	x+ = Left
	x- = Right
	y+ = Up
	y- = Down
	z+ = into screen away from user
	z- = out of screen towards user
	*/

	//*

	//Calculate displacement of colliding objects in the X
	if (impact_From_A->x > impact_From_B->x)
	{
		//	[B]   <- [A]		X<-
		//if A is pushing B left more than B is pushing A left
		//Move B left and A right
		A->move(-xOverlap, 0, 0, true);
		B->move(xOverlap, 0, 0, true);
	}
	else if (impact_From_A->x < impact_From_B->x)
	{
		//	[A]   <- [B]		X<-
		//if B is pushing A left more than A is pushing B left
		//Move A left and B right
		A->move(xOverlap, 0, 0, true);
		B->move(-xOverlap, 0, 0, true);
	}


	//Calculate displacement of colliding objects in the Z
	if (impact_From_A->z < impact_From_B->z)
	{
		// screen| [B]   <- [A]		-Z<- ->+Z
		//if A is pushing B towards user more than B is pushing A towards user
		//AND B is closer to user than A
		//Move B towards user and A into the screen
		A->move(0, 0, zOverlap, true);
		B->move(0, 0, -zOverlap, true);
	}
	else if (impact_From_A->z > impact_From_B->z)
	{
		// screen| [A]   <- [B]		-Z<- ->+Z
		//if B is pushing A towards user more than A is pushing B towards user
		//AND A is closer to user than B
		//Move A towards user and B into the screen
		A->move(0, 0, -zOverlap, true);
		B->move(0, 0, zOverlap, true);
	}


	//Calculate displacement of colliding objects in the Y 
	if (impact_From_A->y > impact_From_B->y && (Asy < Bsy))
	{
		//if A is pushing B up more than B is pushing A up
		//AND B is higher than A
		//Move B up and A down
		A->move(0, -yOverlap, 0, true);
		B->move(0, yOverlap, 0, true);
	}
	else if (impact_From_A->y < impact_From_B->y && (Asy > Bsy))
	{
		//if B is pushing A up more than A is pushing B up
		//AND A is higher than B
		//Move A up and B down
		A->move(0, yOverlap, 0, true);
		B->move(0, -yOverlap, 0, true);
	}

	//if they are the same, then you have to calculate which one is on either side of the world
	if (forcesAreEqual(impact_From_B, impact_From_A))//(impact_From_B == impact_From_A)
	{
		//Calculate Z
		if (Asz < Bsz)
		{
			//if A is closer to the user than B
			//Move A towards user and B away from user
			A->move(0, 0, -zOverlap, true);
			B->move(0, 0, zOverlap, true);
#ifdef DEBUG_SCRIPT_DISPLACEMENT
			std::cout << "\n Object " << A->id_c << " displaced Z: " << -zOverlap;
			std::cout << "\n Object " << B->id_c << " displaced Z: " << zOverlap;
#endif

		}
		else if (Asz > Bsz)
		{
			//if B is closer to the user than A
			//Move B towards user and A away from user
			A->move(0, 0, zOverlap, true);
			B->move(0, 0, -zOverlap, true);
#ifdef DEBUG_SCRIPT_DISPLACEMENT
			std::cout << "\n Object " << A->id_c << " displaced Z: " << zOverlap;
			std::cout << "\n Object " << B->id_c << " displaced Z: " << -zOverlap;
#endif
		}



		//Calculate X
		if (Asx < Bsx)
		{
			//if A is more to the Right than B
			//Move A right and B left
			A->move(-xOverlap, 0, 0, true);
			B->move(xOverlap, 0, 0, true);
#ifdef DEBUG_SCRIPT_DISPLACEMENT
			std::cout << "\n Object " << A->id_c << " displaced X: " << -xOverlap;
			std::cout << "\n Object " << B->id_c << " displaced X: " << xOverlap;
#endif
		}
		else if (Asx > Bsx)
		{
			//if B is more to the Right than A
			//Move B right and A left
			A->move(xOverlap, 0, 0, true);
			B->move(-xOverlap, 0, 0, true);
#ifdef DEBUG_SCRIPT_DISPLACEMENT
			std::cout << "\n Object " << A->id_c << " displaced X: " << xOverlap;
			std::cout << "\n Object " << B->id_c << " displaced X: " << -xOverlap;
#endif
		}

		/*
		//Calculate Y
		if (Asy < Bsy)
		{
		//if A is above B
		//Move A up and B down
		A->move(0, yOverlap, 0);
		B->move(0, -yOverlap, 0);

		}
		else if (Asy > Bsy)
		{
		//if B is above A
		//Move B up and A down
		A->move(0, -yOverlap, 0);
		B->move(0, yOverlap, 0);
		}//*/

	}

	//Remove all forces related to projectiles. Projectiles are destroyed on impact
	for (int i = 0; i < numOfVelocities_A; i++)
	{
		if (A->velocities[i]->velocityType == 1)
		{
			delete(A->velocities[i]);
			A->velocities.erase(A->velocities.begin() + i);
		}
	}
	for (int i = 0; i < numOfVelocities_B; i++)
	{
		if (B->velocities[i]->velocityType == 1)
		{
			delete(B->velocities[i]);
			B->velocities.erase(B->velocities.begin() + i);
		}
	}

	//Add impact velocities to the objects
	//A->addVelocity(impact_From_B);
	//B->addVelocity(impact_From_A);
}
/*
PhysicsEngine::updateVelocitys(std::vector<ObjectType*> objects)

iterates through each object in the vector,
for each of these objects, iterate through each of its Velocitys

apply this Velocity to the object
update this Velocity (decrement timeLeft counter and re-calculate strength)
check to see if this Velocity has no timeLeft, if so erase it from that object
*/
/*IN USE*/void PhysicsEngine::updateVelocities()
{
	int i = 0;
	int numOfObjects = rigidObjects.size();

	int j = 0;
	int numOfVelocitys = 0;

	float curVelocity = 0.0f;

	for (i = 0; i < numOfObjects; i++)
	{
		numOfVelocitys = rigidObjects[i]->velocities.size();//get initial number of velocities before removing dead ones

		for (j = numOfVelocitys - 1; j >= 0; j--)
		{
			//check to see if this Velocity has died
			if (rigidObjects[i]->velocities[j]->isDead())//if (objects[i]->Velocitys[j]->timeLeft < 1)
			{
				//if the Velocity's time is up, then delete it from the vector
				delete(rigidObjects[i]->velocities[j]);
				rigidObjects[i]->velocities.erase(rigidObjects[i]->velocities.begin() + j);
			}
		}

		numOfVelocitys = rigidObjects[i]->velocities.size();//get the number of velocities left alive

		for (j = 0; j < numOfVelocitys; j++)
		{
			//Keep track of current Velocity strength (timeLeft / duration)
			curVelocity = rigidObjects[i]->velocities[j]->strength;

			if (curVelocity > 0.0f)
			{
				//Apply translation to object through Velocity
				rigidObjects[i]->move(
					((curVelocity)* (rigidObjects[i]->velocities[j]->x)),
					((curVelocity)* (rigidObjects[i]->velocities[j]->y)),
					((curVelocity)* (rigidObjects[i]->velocities[j]->z))
					);
			}

			/*Velocity::update() decrements the timeLeft counter, then
			recalculates the strength by taking timeLeft / duration

			This function should be called on every Velocity once per frame*/

			rigidObjects[i]->velocities[j]->update();

			//check to see if the object has moved out of bounds, if so move it to the edge
			//checkScreenBounds(objects[i], true);
		}

		numOfVelocitys = rigidObjects[i]->velocities.size();

		for (j = numOfVelocitys - 1; j > 0; j--)
		{
			//check to see if this Velocity has died
			if (rigidObjects[i]->velocities[j]->isDead())//if (objects[i]->Velocitys[j]->timeLeft < 1)
			{
				//if the Velocity's time is up, then delete it from the vector
				delete(rigidObjects[i]->velocities[j]);
				rigidObjects[i]->velocities.erase(rigidObjects[i]->velocities.begin() + j);
			}
		}
	}
}
void PhysicsEngine::updateVelocities(std::vector<RigidBody*> objects, bool revamp)
{
	int i = 0;
	int numOfObjects = objects.size();

	int j = 0;
	int numOfVelocitys = 0;

	float curVelocity = 0.0f;

	for (i = 0; i < numOfObjects; i++)
	{
		numOfVelocitys = objects[i]->velocities.size();//get initial number of velocities before removing dead ones

		for (j = numOfVelocitys - 1; j >= 0; j--)
		{
			//check to see if this Velocity has died
			if (objects[i]->velocities[j]->isDead())//if (objects[i]->Velocitys[j]->timeLeft < 1)
			{
				//if the Velocity's time is up, then delete it from the vector
				delete(objects[i]->velocities[j]);
				objects[i]->velocities.erase(objects[i]->velocities.begin() + j);
			}
		}

		numOfVelocitys = objects[i]->velocities.size();//get the number of velocities left alive

		for (j = 0; j < numOfVelocitys; j++)
		{
			//Keep track of current Velocity strength (timeLeft / duration)
			curVelocity = objects[i]->velocities[j]->strength;

			if (curVelocity > 0.0f)
			{
				//Apply translation to object through Velocity
				objects[i]->move(
					((curVelocity)* (objects[i]->velocities[j]->x)),
					((curVelocity)* (objects[i]->velocities[j]->y)),
					((curVelocity)* (objects[i]->velocities[j]->z))
					);
			}

			/*Velocity::update() decrements the timeLeft counter, then
			recalculates the strength by taking timeLeft / duration

			This function should be called on every Velocity once per frame*/

			objects[i]->velocities[j]->update();

			//check to see if the object has moved out of bounds, if so move it to the edge
			//checkScreenBounds(objects[i], true);
		}

		numOfVelocitys = objects[i]->velocities.size();

		for (j = numOfVelocitys - 1; j > 0; j--)
		{
			//check to see if this Velocity has died
			if (objects[i]->velocities[j]->isDead())//if (objects[i]->Velocitys[j]->timeLeft < 1)
			{
				//if the Velocity's time is up, then delete it from the vector
				delete(objects[i]->velocities[j]);
				objects[i]->velocities.erase(objects[i]->velocities.begin() + j);
			}
		}
	}
}
void PhysicsEngine::updateVelocities(std::vector<RigidBody*> objects)
{
	int i = 0;
	int numOfObjects = objects.size();

	int j = 0;
	int numOfVelocitys = 0;

	float curVelocity = 0.0f;

	for (i = 0; i < numOfObjects; i++)
	{
		numOfVelocitys = objects[i]->velocities.size();//get initial number of velocities before removing dead ones

		for (j = numOfVelocitys - 1; j >= 0; j--)
		{
			//check to see if this Velocity has died
			if (objects[i]->velocities[j]->isDead())//if (objects[i]->Velocitys[j]->timeLeft < 1)
			{
				//if the Velocity's time is up, then delete it from the vector
				delete(objects[i]->velocities[j]);
				objects[i]->velocities.erase(objects[i]->velocities.begin() + j);
			}
		}

		numOfVelocitys = objects[i]->velocities.size();//get the updated number of velocities

		for (j = 0; j < numOfVelocitys; j++)
		{
			//Keep track of current Velocity strength (timeLeft / duration)
			curVelocity = objects[i]->velocities[j]->strength;

			if (curVelocity > 0.0f)
			{
				//Apply translation to object through Velocity
				objects[i]->move(
					(int)((curVelocity)* (objects[i]->velocities[j]->x)),
					(int)((curVelocity)* (objects[i]->velocities[j]->y)),
					(int)((curVelocity)* (objects[i]->velocities[j]->z))
					);
			}

			/*Velocity::update() decrements the timeLeft counter, then
			recalculates the strength by taking timeLeft / duration

			This function should be called on every Velocity once per frame*/

			objects[i]->velocities[j]->update();

			//check to see if the object has moved out of bounds, if so move it to the edge
			checkScreenBounds(objects[i]);
		}

		numOfVelocitys = objects[i]->velocities.size();

		for (j = numOfVelocitys - 1; j > 0; j--)
		{
			//check to see if this Velocity has died
			if (objects[i]->velocities[j]->isDead())//if (objects[i]->Velocitys[j]->timeLeft < 1)
			{
				//if the Velocity's time is up, then delete it from the vector
				delete(objects[i]->velocities[j]);
				objects[i]->velocities.erase(objects[i]->velocities.begin() + j);
			}
		}
	}
}
void PhysicsEngine::updateVelocities(std::vector<RectObject*> objects)
{
	int i = 0;
	int numOfObjects = objects.size();

	int j = 0;
	int numOfVelocitys = 0;

	float curVelocity = 0.0f;

	for (i = 0; i < numOfObjects; i++)
	{
		numOfVelocitys = objects[i]->velocities.size();

		for (j = numOfVelocitys - 1; j >= 0; j--)
		{
			//check to see if this Velocity has died
			if (objects[i]->velocities[j]->isDead())//if (objects[i]->Velocitys[j]->timeLeft < 1)
			{
				//if the Velocity's time is up, then delete it from the vector
				delete(objects[i]->velocities[j]);
				objects[i]->velocities.erase(objects[i]->velocities.begin() + j);
			}
		}

		numOfVelocitys = objects[i]->velocities.size();

		for (j = 0; j < numOfVelocitys; j++)
		{
			//Keep track of current Velocity strength (timeLeft / duration)
			curVelocity = objects[i]->velocities[j]->strength;

			if (curVelocity > 0.0f)
			{
				//Apply translation to object through Velocity
				objects[i]->move(
					(int)((curVelocity)* (objects[i]->velocities[j]->x)),
					(int)((curVelocity)* (objects[i]->velocities[j]->y))
					//(int)( (curVelocity) * (objects[i]->velocities[j]->z) )
					);
			}



			/*Velocity::update() decrements the timeLeft counter, then
			recalculates the strength by taking timeLeft / duration

			This function should be called on every Velocity once per frame*/

			objects[i]->velocities[j]->update();



			//check to see if the object has moved out of bounds, if so move it to the edge
			checkScreenBounds(objects[i]);
		}

		numOfVelocitys = objects[i]->velocities.size();

		for (j = numOfVelocitys - 1; j > 0; j--)
		{
			//check to see if this Velocity has died
			if (objects[i]->velocities[j]->isDead())//if (objects[i]->Velocitys[j]->timeLeft < 1)
			{
				//if the Velocity's time is up, then delete it from the vector
				delete(objects[i]->velocities[j]);
				objects[i]->velocities.erase(objects[i]->velocities.begin() + j);
			}
		}
	}
}

///MESH
void PhysicsEngine::registerRigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, std::string nameId, int id, float mass)
{
	MeshObject* object = new MeshObject();
	object->Init(obj_filename, v_shader_filename, f_shader_filename);

	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(object, mass, nameId, id));
}
void PhysicsEngine::registerRigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, std::string nameId, float mass)
{
	MeshObject* object = new MeshObject();
	object->Init(obj_filename, v_shader_filename, f_shader_filename);

	int id = rigidObjects.size();
	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(object, mass, nameId, id));
}
void PhysicsEngine::registerRigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, Transform* trans, std::string nameId, int id, float mass)
{
	MeshObject* object = new MeshObject();
	object->Init(obj_filename, v_shader_filename, f_shader_filename);

	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(object, trans, mass, nameId, id));
}
void PhysicsEngine::registerRigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, Transform* trans, std::string nameId, float mass)
{
	MeshObject* object = new MeshObject();
	object->Init(obj_filename, v_shader_filename, f_shader_filename);

	int id = rigidObjects.size();
	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(object, trans, mass, nameId, id));
}
void PhysicsEngine::registerRigidBody(MeshObject* object, std::string nameId, int id, float mass)
{
	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(object, mass, nameId, id));
}
void PhysicsEngine::registerRigidBody(MeshObject* object, std::string nameId, float mass)
{
	int id = rigidObjects.size();
	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(object, mass, nameId, id));
}
void PhysicsEngine::registerRigidBody(MeshObject* object, Transform* trans, std::string nameId, int id, float mass)
{
	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(object, trans, mass, nameId, id));
}
void PhysicsEngine::registerRigidBody(MeshObject* object, Transform* trans, std::string nameId, float mass)
{
	int id = rigidObjects.size();
	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(object, trans, mass, nameId, id));
}
void PhysicsEngine::unregisterRigidBody(std::string nameId)
{
	int numOfObjects = rigidObjects.size();
	for (int i = 0; i < numOfObjects; i++)
	{
		if (rigidObjects[i]->GetName() == nameId)
		{
			delete(rigidObjects[i]);
			rigidObjects.erase(rigidObjects.begin() + i);
			break;//unless you want multiple things with the same name
		}
	}
}
void PhysicsEngine::swapRigidBodyMesh(std::string nameId, MeshObject* pMesh_)
{
	int numOfObjects = rigidObjects.size();
	for (int i = 0; i < numOfObjects; i++)
	{
		if (rigidObjects[i]->GetName() == nameId)
		{
			rigidObjects[i]->pMesh = pMesh_;
			break;//unless you want multiple things with the same name
		}
	}
}

/*
PhysicsEngine::addVelocityTo takes in a string nameId as the key for a map
searches through a multimap for every instance that has the key nameId
this returns a std::pair of the iterators first instance of that key
and the last instance of that key so you would iterate through from
pair.first and pair.second

we then take each of those iterators, which would be the key,value pair
of strind,RigidBody*

and we then call it->second (which translates to RigidBody->)
and add the velocity passed in to that RigidBody object
*/
void PhysicsEngine::addVelocityTo(std::string nameId, Velocity* velocity)
{
	/*
	std::pair <std::multimap<std::string, RigidBody*>::iterator, std::multimap<std::string, RigidBody*>::iterator> ret;
	ret = rigidObjects.equal_range(nameId);

	std::map<std::string, RigidBody*>::iterator it;

	for (it = ret.first; it != ret.second; ++it)
	{
	it->second->addVelocity(velocity);
	}//*/

	int numOfObjects = rigidObjects.size();
	for (int i = 0; i < numOfObjects; i++)
	{
		if (rigidObjects[i]->GetName() == nameId)
		{
			rigidObjects[i]->addVelocity(velocity);
			break;//unless you want multiple things with the same name
		}
	}

}


///QUAD TREE / COLLISIONS
vector<std::pair<RigidBody*, RigidBody*>> PhysicsEngine::listCollisions()
{
	/*
	Once all objects have been inserted,
	you will go through each object and retrieve a
	list of objects it could possibly collide with.
	You'll then check for collisions between each
	object in the list and the initial object,
	using a collision detection algorithm.
	//*/

	vector<std::pair<RigidBody*, RigidBody*>>collidedObjects = vector<std::pair<RigidBody*, RigidBody*>>();

	int numOfObjects = rigidObjects.size();

	list<RigidBody*> returnObjects = list<RigidBody*>();

	for (int i = 0; i < numOfObjects; i++)
	{
		returnObjects.clear();
		quadtree.retrieve(&returnObjects, rigidObjects[i]);

#ifdef DEBUG_SCRIPT
		cout << "\n object:" << rigidObjects[i]->id_c << " vs";
#endif

		for (list<RigidBody*>::iterator it = returnObjects.begin(); it != returnObjects.end(); ++it)
		{

			RigidBody* cur = *it;

			if (cur->id != rigidObjects[i]->id)
			{
#ifdef DEBUG_SCRIPT
				cout << "\n object:" << cur->id_c;
#endif

				bool hit = collisions.checkCollisionAAB(
					cur->pMesh->boundingBox.center.x, cur->pMesh->boundingBox.center.y, cur->pMesh->boundingBox.center.z,
					cur->pMesh->boundingBox.xRadius, cur->pMesh->boundingBox.yRadius, cur->pMesh->boundingBox.zRadius,
					rigidObjects[i]->pMesh->boundingBox.center.x, rigidObjects[i]->pMesh->boundingBox.center.y, rigidObjects[i]->pMesh->boundingBox.center.z,
					rigidObjects[i]->pMesh->boundingBox.xRadius, rigidObjects[i]->pMesh->boundingBox.yRadius, rigidObjects[i]->pMesh->boundingBox.zRadius
					);
				if (hit)
				{
#ifdef DEBUG_SCRIPT
					cout << "\n HIT " << rigidObjects[i]->id_c << " vs " << cur->id_c;
#endif

					//triggerImpact(cur, rigidObjects[i]);
					collidedObjects.push_back(std::pair<RigidBody*, RigidBody*>(cur, rigidObjects[i]));
				}
			}

		}
	}//*/

	return collidedObjects;
}
vector<RigidBody*> PhysicsEngine::listCollisions(std::string nameId)
{

	int numOfObjects = rigidObjects.size();

	vector<RigidBody*> collidedObjects = vector<RigidBody*>();
	list<RigidBody*> returnObjects = list<RigidBody*>();

	for (int i = 0; i < numOfObjects; i++)
	{

		if (rigidObjects[i]->GetName() == nameId)
		{
			RigidBody* targetObject = rigidObjects[i];

			returnObjects.clear();
			quadtree.retrieve(&returnObjects, targetObject);



			for (list<RigidBody*>::iterator it = returnObjects.begin(); it != returnObjects.end(); ++it)
			{

				RigidBody* cur = *it;

				if (cur->id != targetObject->id)
				{
#ifdef DEBUG_SCRIPT
					cout << "\n object:" << cur->id_c;
#endif

					bool hit = collisions.checkCollisionAAB(
						cur->pMesh->boundingBox.center.x, cur->pMesh->boundingBox.center.y, cur->pMesh->boundingBox.center.z,
						cur->pMesh->boundingBox.xRadius, cur->pMesh->boundingBox.yRadius, cur->pMesh->boundingBox.zRadius,
						targetObject->pMesh->boundingBox.center.x, targetObject->pMesh->boundingBox.center.y, targetObject->pMesh->boundingBox.center.z,
						targetObject->pMesh->boundingBox.xRadius, targetObject->pMesh->boundingBox.yRadius, targetObject->pMesh->boundingBox.zRadius
						);
					if (hit)
					{
#ifdef DEBUG_SCRIPT
						cout << "\n HIT " << targetObject->id_c << " vs " << cur->id_c;
#endif

						//triggerImpact(cur, rigidObjects[i]);
						collidedObjects.push_back(cur);
					}
				}

			}
		}//*/



		break;//unless you want multiple things with the same name
	}

	return collidedObjects;
}
vector<std::pair<RigidBody*, RigidBody*>> PhysicsEngine::listCollisions(vector<RigidBody*> list)
{
	vector<std::pair<RigidBody*, RigidBody*>> collidedObjectPairs = vector<std::pair<RigidBody*, RigidBody*>>();
	int givenListSize = list.size();
	for (int i = 0; i < givenListSize; i++)
	{
		vector<RigidBody*> collidedObjects = listCollisions(list[i]->GetName());
		int collidedObjectsSize = collidedObjects.size();

		for (int j = 0; j < collidedObjectsSize; j++)
		{
			collidedObjectPairs.push_back(std::pair<RigidBody*, RigidBody*>(list[i], collidedObjects[j]));
		}
	}

	return collidedObjectPairs;
}

bool PhysicsEngine::hasCollided(std::string nameId1, std::string nameId2)
{
	int numOfObjects = rigidObjects.size();

	RigidBody* obj1 = new RigidBody();
	RigidBody* obj2 = new RigidBody();

	for (int i = 0; i < numOfObjects; i++)
	{
		if (rigidObjects[i]->GetName() == nameId1)
		{
			obj1 = rigidObjects[i];
		}
	}
	for (int i = 0; i < numOfObjects; i++)
	{
		if (rigidObjects[i]->GetName() == nameId2)
		{
			obj2 = rigidObjects[i];
		}
	}

	return collisions.checkCollisionAAB(
		obj1->pMesh->boundingBox.center.x, obj1->pMesh->boundingBox.center.y, obj1->pMesh->boundingBox.center.z,
		obj1->pMesh->boundingBox.xRadius, obj1->pMesh->boundingBox.yRadius, obj1->pMesh->boundingBox.zRadius,
		obj2->pMesh->boundingBox.center.x, obj2->pMesh->boundingBox.center.y, obj2->pMesh->boundingBox.center.z,
		obj2->pMesh->boundingBox.xRadius, obj2->pMesh->boundingBox.yRadius, obj2->pMesh->boundingBox.zRadius
		);
}

bool PhysicsEngine::hasHitProjectile(std::string nameId)
{
	vector<RigidBody*> collidedObjects = listCollisions(nameId);
	int numOfObjects = collidedObjects.size();

	for (int i = 0; i < numOfObjects; i++)
	{
		if (collidedObjects[i]->isProjectile())
		{
			return true;
		}
	}
}
RigidBody* PhysicsEngine::hasHitProjectile(std::string nameId, bool returnRigidBody)
{
	vector<RigidBody*> collidedObjects = listCollisions(nameId);
	int numOfObjects = collidedObjects.size();

	for (int i = 0; i < numOfObjects; i++)
	{
		if (collidedObjects[i]->isProjectile())
		{
			return collidedObjects[i];
		}
	}
}
vector<RigidBody*> PhysicsEngine::hasHitProjectile(vector<RigidBody*> list)
{
	vector<RigidBody*> objectsThatHitProjectile = vector<RigidBody*>();
	int givenListSize = list.size();
	for (int i = 0; i < givenListSize; i++)
	{
		vector<RigidBody*> collidedObjects = listCollisions(list[i]->GetName());
		int collidedObjectsSize = collidedObjects.size();

		for (int j = 0; j < collidedObjectsSize; j++)
		{
			if (collidedObjects[j]->isProjectile())
			{
				objectsThatHitProjectile.push_back(list[i]);//collidedObjects[j]
			}
		}
	}

	return objectsThatHitProjectile;
}
vector<std::pair<RigidBody*, RigidBody*>> PhysicsEngine::hasHitProjectile(vector<RigidBody*> list, bool returnPairs)
{
	vector<std::pair<RigidBody*, RigidBody*>> objectsThatHitProjectile = vector<std::pair<RigidBody*, RigidBody*>>();
	int givenListSize = list.size();
	for (int i = 0; i < givenListSize; i++)
	{
		vector<RigidBody*> collidedObjects = listCollisions(list[i]->GetName());
		int collidedObjectsSize = collidedObjects.size();

		for (int j = 0; j < collidedObjectsSize; j++)
		{
			if (collidedObjects[j]->isProjectile())
			{
				objectsThatHitProjectile.push_back(std::pair<RigidBody*, RigidBody*>(list[i], collidedObjects[j]));
			}
		}
	}

	return objectsThatHitProjectile;
}
vector<std::pair<RigidBody*, bool>> PhysicsEngine::hasHitProjectile(vector<RigidBody*> list, bool returnPairs, bool returnBools)
{
	vector<std::pair<RigidBody*, bool>> objectsThatHitProjectile = vector<std::pair<RigidBody*, bool>>();
	int givenListSize = list.size();
	for (int i = 0; i < givenListSize; i++)
	{
		vector<RigidBody*> collidedObjects = listCollisions(list[i]->GetName());
		int collidedObjectsSize = collidedObjects.size();

		for (int j = 0; j < collidedObjectsSize; j++)
		{
			if (collidedObjects[j]->isProjectile())
			{
				objectsThatHitProjectile.push_back(std::pair<RigidBody*, bool>(list[i], true));
			}
		}
	}

	return objectsThatHitProjectile;
}

void PhysicsEngine::quadTreeCollision()
{
	/*
	Once all objects have been inserted,
	you will go through each object and retrieve a
	list of objects it could possibly collide with.
	You'll then check for collisions between each
	object in the list and the initial object,
	using a collision detection algorithm.
	//*/

	int numOfObjects = rigidObjects.size();

	list<RigidBody*> returnObjects = list<RigidBody*>();

	for (int i = 0; i < numOfObjects; i++)
	{
		returnObjects.clear();
		quadtree.retrieve(&returnObjects, rigidObjects[i]);

#ifdef DEBUG_SCRIPT
		cout << "\n object:" << rigidObjects[i]->id_c << " vs";
#endif


		for (list<RigidBody*>::iterator it = returnObjects.begin(); it != returnObjects.end(); ++it)
		{

			RigidBody* cur = *it;

			if (cur->id != rigidObjects[i]->id)
			{
				#ifdef DEBUG_SCRIPT
					cout << "\n object:" << cur->id_c;
				#endif

				bool hit = collisions.checkCollisionAAB(
					cur->pMesh->boundingBox.center.x, cur->pMesh->boundingBox.center.y, cur->pMesh->boundingBox.center.z,
					cur->pMesh->boundingBox.xRadius, cur->pMesh->boundingBox.yRadius, cur->pMesh->boundingBox.zRadius,
					rigidObjects[i]->pMesh->boundingBox.center.x, rigidObjects[i]->pMesh->boundingBox.center.y, rigidObjects[i]->pMesh->boundingBox.center.z,
					rigidObjects[i]->pMesh->boundingBox.xRadius, rigidObjects[i]->pMesh->boundingBox.yRadius, rigidObjects[i]->pMesh->boundingBox.zRadius
					);
				if (hit)
				{
					#ifdef PRINT_COLLISION
					cout << "\n HIT " << rigidObjects[i]->id_c << " vs " << cur->id_c;
					#endif
					
					triggerImpact(cur, rigidObjects[i]);
				}
			}

		}
	}//*/
}
void PhysicsEngine::bruteCollision()
{
	int numOfObjects = rigidObjects.size();

	list<RigidBody*> returnObjects = list<RigidBody*>();

	for (int i = 0; i < numOfObjects; i++)
	{
		returnObjects.push_back(rigidObjects[i]);
	}
	for (int i = 0; i < numOfObjects; i++)
	{
#ifdef DEBUG_SCRIPT
		cout << "\n object:" << rigidObjects[i]->id_c << " vs";
#endif


		for (list<RigidBody*>::iterator it = returnObjects.begin(); it != returnObjects.end(); ++it)
		{

			RigidBody* cur = *it;

#ifdef DEBUG_SCRIPT
			cout << "\n object:" << cur->id_c;
#endif

			if (cur->id != rigidObjects[i]->id)
			{
				bool hit = collisions.checkCollisionAAB(
					cur->pMesh->boundingBox.center.x, cur->pMesh->boundingBox.center.y, cur->pMesh->boundingBox.center.z,
					cur->pMesh->boundingBox.xRadius, cur->pMesh->boundingBox.yRadius, cur->pMesh->boundingBox.zRadius,
					rigidObjects[i]->pMesh->boundingBox.center.x, rigidObjects[i]->pMesh->boundingBox.center.y, rigidObjects[i]->pMesh->boundingBox.center.z,
					rigidObjects[i]->pMesh->boundingBox.xRadius, rigidObjects[i]->pMesh->boundingBox.yRadius, rigidObjects[i]->pMesh->boundingBox.zRadius
					);
				if (hit)
				{
					cout << "\n HIT " << rigidObjects[i]->id_c << " vs " << cur->id_c;
					triggerImpact(cur, rigidObjects[i]);
				}
			}

		}
	}//*/
}
void PhysicsEngine::updateQuadTree()
{
	//At every frame, you will insert all objects into the quadtree by
	//first clearing the quadtree then using the insert method for every object.

	int numOfObjects = rigidObjects.size();

	quadtree.clear();

	for (int i = 0; i < numOfObjects; i++) {
		quadtree.insert(rigidObjects[i]);
	}

}

///VALIDATION
bool PhysicsEngine::forcesAreEqual(Velocity* v1, Velocity* v2)
{
	if (v1->x == v2->x && v1->y == v2->y && v1->z == v2->z)
	{
		return true;
	}
	return false;
}
void PhysicsEngine::checkScreenBounds(RigidBody* object)
{
	float object_sx = object->pMesh->bottomFace.sx;
	float object_sz = object->pMesh->bottomFace.sy;
	float object_ex = object->pMesh->bottomFace.ex;
	float object_ez = object->pMesh->bottomFace.ey;

	if (object_sx < 0)
	{
		object->move(-(object_sx), 0, 0);
		int numOfVelocities = object->velocities.size();
		for (int i = 0; i < numOfVelocities; i++)
		{
			if (object->velocities[i]->velocityType == 1)
			{
				object->velocities.erase(object->velocities.begin() + i);
			}
		}
	}
	if (object_sz < 0)
	{
		object->move(0, 0, -(object_sz));
		int numOfVelocities = object->velocities.size();
		for (int i = 0; i < numOfVelocities; i++)
		{
			if (object->velocities[i]->velocityType == 1)
			{
				object->velocities.erase(object->velocities.begin() + i);
			}
		}
	}
	if (object_ex > screenWidth)
	{
		int diff = object_ex - screenWidth;
		object->move(-diff, 0, 0);
		int numOfVelocities = object->velocities.size();
		for (int i = 0; i < numOfVelocities; i++)
		{
			if (object->velocities[i]->velocityType == 1)
			{
				object->velocities.erase(object->velocities.begin() + i);
			}
		}
	}
	if (object_ez > screenHeight)
	{
		int diff = object_ez - screenDepth;
		object->move(0, 0, -diff);
		int numOfVelocities = object->velocities.size();
		for (int i = 0; i < numOfVelocities; i++)
		{
			if (object->velocities[i]->velocityType == 1)
			{
				object->velocities.erase(object->velocities.begin() + i);
			}
		}
	}
}
void PhysicsEngine::checkScreenBounds(RectObject* object)
{

	if (object->sx < 0)
	{
		object->move(-(object->sx), 0);
		int numOfVelocities = object->velocities.size();
		for (int i = 0; i < numOfVelocities; i++)
		{
			if (object->velocities[i]->velocityType == 1)
			{
				object->velocities.erase(object->velocities.begin() + i);
			}
		}
	}
	if (object->sy < 0)
	{
		object->move(0, -(object->sy));
		int numOfVelocities = object->velocities.size();
		for (int i = 0; i < numOfVelocities; i++)
		{
			if (object->velocities[i]->velocityType == 1)
			{
				object->velocities.erase(object->velocities.begin() + i);
			}
		}
	}
	if (object->ex > screenWidth)
	{
		int diff = object->ex - screenWidth;
		object->move(-diff, 0);
		int numOfVelocities = object->velocities.size();
		for (int i = 0; i < numOfVelocities; i++)
		{
			if (object->velocities[i]->velocityType == 1)
			{
				object->velocities.erase(object->velocities.begin() + i);
			}
		}
	}
	if (object->ey > screenHeight)
	{
		int diff = object->ey - screenHeight;
		object->move(0, -diff);
		int numOfVelocities = object->velocities.size();
		for (int i = 0; i < numOfVelocities; i++)
		{
			if (object->velocities[i]->velocityType == 1)
			{
				object->velocities.erase(object->velocities.begin() + i);
			}
		}
	}
}