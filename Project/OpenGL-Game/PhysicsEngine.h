

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

//
#include "Collisions.h"
#include "RigidBody.h"
#include "Quadtree.h"
//

#include "openGL.h"
#include "Math.h"

#include "Velocity.h"

#include "RectObject.h"//Object must include BoundingBox.h
//#include "BoundingBox.h"

#include <vector>
#include <map>

/*
*/

class PhysicsEngine
{
public:
	Collisions collisions;
	Quadtree quadtree;

	PhysicsEngine();
	PhysicsEngine(int screenWidth_, int screenHeight_); // 2D
	PhysicsEngine(int screenWidth_, int screenHeight_, int screenDepth_); // 3D


	void applyVelocity(RectObject* object, Velocity f);
	void applyVelocity(RectObject* object, Velocity* f);
	void applyVelocity(RectObject* object, float x_, float y_, float z_, int type_, int duration_ = 10);
	//void applyVelocity(RigidBody* object, Velocity f);
	//void applyVelocity(RigidBody* object, Velocity* f);
	//void applyVelocity(RigidBody* object, float x_, float y_, float z_, int type_, int duration_ = 10);

	void ApplyVelocities();


	/*
	PhysicsEngine::updateVelocitys(std::vector<ObjectType*> objects)

	iterates through each object in the vector,
	for each of these objects, iterate through each of its Velocities

	apply this Velocity to the object
	update this Velocity (decrement timeLeft counter and re-calculate strength)
	check to see if this Velocity has no timeLeft, if so erase it from that object
	*/
	void updateVelocities(std::vector<RectObject*> objects);
	void updateVelocities(std::vector<RigidBody*> objects);
	void updateVelocities(std::vector<RigidBody*> objects, bool revamp);
	void updateVelocities();

	void triggerImpact(RectObject* A, RectObject* B);
	void triggerImpact(RigidBody* A, RigidBody* B);
	void triggerImpact(RigidBody* A, RigidBody* B, bool prep);

	///COLLISIONS
	vector<std::pair<RigidBody*, RigidBody*>> listCollisions();
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

	void updateQuadTree();
	void quadTreeCollision();
	void bruteCollision();

	void registerRigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, std::string nameId, int id, float mass = 1);
	void registerRigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, std::string nameId, float mass = 1);
	void registerRigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, Transform* trans, std::string nameId, int id, float mass = 1);
	void registerRigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, Transform* trans, std::string nameId, float mass = 1);
	void registerRigidBody(MeshObject* object, std::string nameId, int id, float mass = 1);
	void registerRigidBody(MeshObject* object, std::string nameId, float mass = 1);
	void registerRigidBody(MeshObject* object, Transform* trans, std::string nameId, float mass = 1);
	void registerRigidBody(MeshObject* object, Transform* trans, std::string nameId, int id, float mass = 1);
	void unregisterRigidBody(std::string nameId);
	void swapRigidBodyMesh(std::string nameId, MeshObject* pMesh_);

	void addVelocityTo(std::string nameId, Velocity* velocity);

	bool forcesAreEqual(Velocity* v1, Velocity* v2);

	void checkScreenBounds(RectObject* object);
	void checkScreenBounds(RigidBody* object);

	vector<RigidBody*> rigidObjects;

	int screenWidth;
	int screenHeight;
	int screenDepth;
};


#endif

