
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
	rigidObjects = vector<RigidBody*>();

	idCounter = 0;
}
PhysicsEngine::PhysicsEngine(int screenWidth_, int screenHeight_)
{
	screenWidth = screenWidth_;
	screenHeight = screenHeight_;
	screenDepth = screenHeight_;

	collisions = Collisions();
	rigidObjects = vector<RigidBody*>();
	idCounter = 0;
}
PhysicsEngine::PhysicsEngine(int screenWidth_, int screenHeight_, int screenDepth_)
{
	screenWidth = screenWidth_;
	screenHeight = screenHeight_;
	screenDepth = screenDepth_;

	collisions = Collisions();
	rigidObjects = vector<RigidBody*>();
	idCounter = 0;
}

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

	if (A->isProjectile()) netVeloA = A->NetVelocityX();

	xTotal_A += netVeloA.x;// -abs((A->boundingBox->xRadius + A->boundingBox->center.x) - (B->boundingBox->xRadius + B->boundingBox->center.x));
	yTotal_A += netVeloA.y;
	zTotal_A += netVeloA.z;// -abs((A->boundingBox->zDepth + A->boundingBox->center.z) - (B->boundingBox->zDepth + B->boundingBox->center.z));

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


	A->addVelocity(new Velocity(*impact_From_B));
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
				j--;
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
			curVelocity = rigidObjects[i]->velocities[j]->strength * timeDelta;

			if (curVelocity > 0.0f)
			{
				//Apply translation to object through Velocity
				if (rigidObjects[i]->isProjectile()) {
					rigidObjects[i]->move(
						((curVelocity)* (rigidObjects[i]->velocities[j]->x)),
						((curVelocity)* (rigidObjects[i]->velocities[j]->y)),
						((curVelocity)* (rigidObjects[i]->velocities[j]->z)),
						true);
				}
				else if (rigidObjects[i]->isEnvironment() == false) {
					rigidObjects[i]->move(
						((curVelocity)* (rigidObjects[i]->velocities[j]->x)),
						((curVelocity)* (rigidObjects[i]->velocities[j]->y)),
						((curVelocity)* (rigidObjects[i]->velocities[j]->z))
						);
				}
			}
		}
	}
}



///MESH
void PhysicsEngine::registerRigidBody(BoundingBox* box, Transform* trans, std::string nameId, int type, float mass)
{
	int id = idCounter++;
	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	RigidBody* temp = new RigidBody(box, trans, mass, nameId, id);
	temp->setType(type);
	rigidObjects.push_back(temp);
}
void PhysicsEngine::registerRigidBody(BoundingBox* box, Transform* trans, std::string nameId, float mass)
{
	int id = idCounter++;
	//RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	//rigidObjects.insert(std::pair<std::string, RigidBody*>(nameId, new RigidBody(object, mass, nameId, id)));
	rigidObjects.push_back(new RigidBody(box, trans, mass, nameId, id));
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
void PhysicsEngine::swapRigidBodyTrans(std::string nameId, Transform* pTrans_)
{
	int numOfObjects = rigidObjects.size();
	for (int i = 0; i < numOfObjects; i++)
	{
		if (rigidObjects[i]->GetName() == nameId)
		{
			rigidObjects[i]->pTrans = pTrans_;
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
		returnObjects.push_back(rigidObjects[i]);
	}

	for (int i = 0; i < numOfObjects; i++)
	{
/*
		returnObjects.clear();
		quadtree.retrieve(&returnObjects, rigidObjects[i]);*/

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
					cur->boundingBox->center.x, cur->boundingBox->center.y, cur->boundingBox->center.z,
					cur->boundingBox->xRadius, cur->boundingBox->yRadius, cur->boundingBox->zRadius,
					rigidObjects[i]->boundingBox->center.x, rigidObjects[i]->boundingBox->center.y, rigidObjects[i]->boundingBox->center.z,
					rigidObjects[i]->boundingBox->xRadius, rigidObjects[i]->boundingBox->yRadius, rigidObjects[i]->boundingBox->zRadius
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
vector<Transform*> PhysicsEngine::listCollisionsTransform(std::string nameId)
{

	int numOfObjects = rigidObjects.size();

	vector<Transform*> collidedObjects = vector<Transform*>();

	for (int i = 0; i < numOfObjects; i++)
	{
		if (rigidObjects[i]->GetName() == nameId)
		{
			RigidBody* targetObject = rigidObjects[i];

			for (size_t count = 0; count < rigidObjects.size(); count++)
			{
				RigidBody* cur = rigidObjects[count];

				if (cur->id != targetObject->id)
				{
#ifdef DEBUG_SCRIPT
					cout << "\n object:" << cur->id_c;
#endif

					bool hit = collisions.checkCollisionAAB(
						cur->boundingBox->center.x, cur->boundingBox->center.y, cur->boundingBox->center.z,
						cur->boundingBox->xRadius, cur->boundingBox->yRadius, cur->boundingBox->zRadius,
						targetObject->boundingBox->center.x, targetObject->boundingBox->center.y, targetObject->boundingBox->center.z,
						targetObject->boundingBox->xRadius, targetObject->boundingBox->yRadius, targetObject->boundingBox->zRadius
						);
					if (hit)
					{
#ifdef DEBUG_SCRIPT
						cout << "\n HIT " << targetObject->id_c << " vs " << cur->id_c;
#endif

						//triggerImpact(cur, rigidObjects[i]);
						collidedObjects.push_back(cur->pTrans);
					}
				}

			}
		}//*/

	}

	return collidedObjects;
}
vector<RigidBody*> PhysicsEngine::listCollisions(std::string nameId)
{

	int numOfObjects = rigidObjects.size();

	vector<RigidBody*> collidedObjects = vector<RigidBody*>();

	for (int i = 0; i < numOfObjects; i++)
	{
		if (rigidObjects[i]->GetName() == nameId)
		{
			RigidBody* targetObject = rigidObjects[i];

			for (size_t count = 0; count < rigidObjects.size(); count++)
			{
				RigidBody* cur = rigidObjects[count];

				if (cur->id != targetObject->id)
				{
#ifdef DEBUG_SCRIPT
					cout << "\n object:" << cur->id_c;
#endif

					bool hit = collisions.checkCollisionAAB(
						cur->boundingBox->center.x, cur->boundingBox->center.y, cur->boundingBox->center.z,
						cur->boundingBox->xRadius, cur->boundingBox->yRadius, cur->boundingBox->zRadius,
						targetObject->boundingBox->center.x, targetObject->boundingBox->center.y, targetObject->boundingBox->center.z,
						targetObject->boundingBox->xRadius, targetObject->boundingBox->yRadius, targetObject->boundingBox->zRadius
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
		obj1->boundingBox->center.x, obj1->boundingBox->center.y, obj1->boundingBox->center.z,
		obj1->boundingBox->xRadius, obj1->boundingBox->yRadius, obj1->boundingBox->zRadius,
		obj2->boundingBox->center.x, obj2->boundingBox->center.y, obj2->boundingBox->center.z,
		obj2->boundingBox->xRadius, obj2->boundingBox->yRadius, obj2->boundingBox->zRadius
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

void PhysicsEngine::bruteCollision()
{
	int numOfObjects = rigidObjects.size();

	list<RigidBody*> returnObjects = list<RigidBody*>();

	for (int i = 0; i < numOfObjects; i++)
	{
		rigidObjects[i]->updateBoundingBox();
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

			if (cur->id != rigidObjects[i]->id && !((cur->getType() == 3 && rigidObjects[i]->getType() == 4) || (cur->getType() == 4 && rigidObjects[i]->getType() == 3)))
			{
				bool hit = collisions.checkCollisionAAB(
					cur->boundingBox->center.x, cur->boundingBox->center.y, cur->boundingBox->center.z,
					cur->boundingBox->xRadius, cur->boundingBox->yRadius, cur->boundingBox->zRadius,
					rigidObjects[i]->boundingBox->center.x, rigidObjects[i]->boundingBox->center.y, rigidObjects[i]->boundingBox->center.z,
					rigidObjects[i]->boundingBox->xRadius, rigidObjects[i]->boundingBox->yRadius, rigidObjects[i]->boundingBox->zRadius
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

///VALIDATION
bool PhysicsEngine::forcesAreEqual(Velocity* v1, Velocity* v2)
{
	if (v1->x == v2->x && v1->y == v2->y && v1->z == v2->z)
	{
		return true;
	}
	return false;
}
