

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

//
#include "Collisions.h"
#include "RigidBody.h"
//

#include "openGL.h"
#include "Math.h"

#include "Velocity.h"

#include <list>
#include <vector>
#include <map>
#include "Transform.h"

using namespace std;

/*
*/

class PhysicsEngine
{
public:
	Collisions collisions;

	PhysicsEngine();
	PhysicsEngine(int screenWidth_, int screenHeight_); // 2D
	PhysicsEngine(int screenWidth_, int screenHeight_, int screenDepth_); // 3D

	void ApplyVelocities();
	void ApplyVelocities(float timeDelta);

	/*
	PhysicsEngine::updateVelocitys(std::vector<ObjectType*> objects)

	iterates through each object in the vector,
	for each of these objects, iterate through each of its Velocities

	apply this Velocity to the object
	update this Velocity (decrement timeLeft counter and re-calculate strength)
	check to see if this Velocity has no timeLeft, if so erase it from that object
	*/
	void updateVelocities();

	void triggerImpact(RigidBody* A, RigidBody* B);

	///COLLISIONS
	vector<std::pair<RigidBody*, RigidBody*>> listCollisions();
	vector<Transform*> listCollisionsTransform(std::string nameId);
	vector<RigidBody*> listCollisions(std::string nameId);
	vector<std::pair<RigidBody*, RigidBody*>> listCollisions(vector<RigidBody*> list);

	bool hasCollided(std::string nameId1, std::string nameId2);

	bool hasHitProjectile(std::string nameId);
	RigidBody* hasHitProjectile(std::string nameId, bool returnRigidBody);
	vector<RigidBody*> hasHitProjectile(vector<RigidBody*> list);
	vector<std::pair<RigidBody*, bool>> hasHitProjectile(vector<RigidBody*> list, bool returnPairs, bool returnBool);
	vector<std::pair<RigidBody*, RigidBody*>> hasHitProjectile(vector<RigidBody*> list, bool returnPairs);
	/*
	return->first is an object passed into this function, return->second is what that has collided with
	*/

	void bruteCollision();

	void registerRigidBody(BoundingBox* box, Transform* trans, std::string nameId, float mass = 1);
	void registerRigidBody(BoundingBox* box, Transform* trans, std::string nameId, int type, float mass = 1);

	void unregisterRigidBody(std::string nameId);
	void swapRigidBodyTrans(std::string nameId, Transform* pTrans_);

	void addVelocityTo(std::string nameId, Velocity* velocity);

	bool forcesAreEqual(Velocity* v1, Velocity* v2);

	vector<RigidBody*> rigidObjects;

	int screenWidth;
	int screenHeight;
	int screenDepth;
	int idCounter;
};


#endif

