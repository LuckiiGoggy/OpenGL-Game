
#include "PhysicsEngine.h"

//#define DEBUG_SCRIPT
#define DEBUG_SCRIPT_DISPLACEMENT
#define PRINT_COLLISION

PhysicsEngine::PhysicsEngine()
{
	screenWidth = 566;
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




void PhysicsEngine::triggerImpact(RigidBody *A, RigidBody *B)
{
	int numOfVelocities_A = A->velocities.size();
	int numOfVelocities_B = B->velocities.size();

	float xTotal_A = 0;//total x influence (total velocity in the x direction) for object A
	float yTotal_A = 0;//total y influence for object A
	float zTotal_A = 0;//total z influence for object A

	float xImpact_A = 0;//resulting x impact influence created from object A
	float yImpact_A = 0;//resulting y impact influence created from object A
	float zImpact_A = 0;//resulting z impact influence created from object A

	float xTotal_B = 0;//total x influence (total velocity in the x direction) for object A
	float yTotal_B = 0;//total y influence for object A
	float zTotal_B = 0;//total z influence for object A

	float xImpact_B = 0;//resulting x impact influence created from object A
	float yImpact_B = 0;//resulting y impact influence created from object A
	float zImpact_B = 0;//resulting z impact influence created from object A

	//Sum all of the velocities to get the total influence for object A
	glm::vec3 netVeloA = A->NetVelocity();

	xTotal_A += netVeloA.x;// -abs((A->pMesh->boundingBox.xRadius + A->pMesh->boundingBox.center.x) - (B->pMesh->boundingBox.xRadius + B->pMesh->boundingBox.center.x));
	yTotal_A += netVeloA.y;
	zTotal_A += netVeloA.z;// -abs((A->pMesh->boundingBox.zDepth + A->pMesh->boundingBox.center.z) - (B->pMesh->boundingBox.zDepth + B->pMesh->boundingBox.center.z));

	//Sum all of the velocities to get the total influence for object A
	glm::vec3 netVeloB = A->NetVelocityX();

	xTotal_B += netVeloB.x;
	yTotal_B += netVeloB.y;
	zTotal_B += netVeloB.z;

	//Impact = velocity * mass
	xImpact_A = xTotal_A * (A->mass / B->mass); //PA
	yImpact_A = yTotal_A * (A->mass / B->mass);
	zImpact_A = zTotal_A * (A->mass / B->mass);

	//Impact = velocity * mass
	xImpact_B = xTotal_B * (B->mass / A->mass); //PA
	yImpact_B = yTotal_B * (B->mass / A->mass);
	zImpact_B = zTotal_B * (B->mass / A->mass);


	//resulting velocities from collision
	Velocity* impact_From_A = new Velocity(xImpact_A, yImpact_A, zImpact_A, 3, 3);
	Velocity* impact_From_B = new Velocity(-xImpact_B, -yImpact_B, -zImpact_B, 3, 2);


	//A->addVelocity(new Velocity(*impact_From_B));
	B->addVelocity(new Velocity(*impact_From_A));
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
	int numOfObjects = rigidObjects.size();

	float curVelocity = 0.0f;

	for (int i = 0; i < numOfObjects; i++)
	{

		for (int j = 0; j < rigidObjects[i]->velocities.size(); j++)
		{

			/*Velocity::update() decrements the timeLeft counter, then
			recalculates the strength by taking timeLeft / duration

			This function should be called on every Velocity once per frame*/

			rigidObjects[i]->velocities[j]->update();

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

void PhysicsEngine::ApplyVelocities(){}

void PhysicsEngine::ApplyVelocities(float timeDelta){
	int i = 0;
	int numOfObjects = rigidObjects.size();

	int j = 0;
	int numOfVelocitys = 0;

	float curVelocity = 0.0f;

	for (i = 0; i < numOfObjects; i++)
	{
		numOfVelocitys = rigidObjects[i]->velocities.size();//get the number of velocities left alive

		for (j = 0; j < numOfVelocitys; j++)
		{
			//Keep track of current Velocity strength (timeLeft / duration)
			curVelocity = rigidObjects[i]->velocities[j]->strength;

			if (curVelocity > 0.0f)
			{
				//Apply translation to object through Velocity
				rigidObjects[i]->move(
					((curVelocity)* (rigidObjects[i]->velocities[j]->x) * timeDelta),
					((curVelocity)* (rigidObjects[i]->velocities[j]->y) * timeDelta),
					((curVelocity)* (rigidObjects[i]->velocities[j]->z) * timeDelta)
					);
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