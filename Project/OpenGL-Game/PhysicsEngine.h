

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "openGL.h"
#include "Math.h"

#include "Velocity.h"

#include "RectObject.h"//Object must include BoundingBox.h
//#include "BoundingBox.h"

#include <vector>

/* 
*/

class PhysicsEngine
{
public:

	PhysicsEngine();
	PhysicsEngine(int screenWidth_, int screenHeight_);


	void applyVelocity(RectObject* object, Velocity f);
	void applyVelocity(RectObject* object, Velocity* f);
	void applyVelocity(RectObject* object, float x_, float y_, float z_, int type_, int duration_ = 10);

	/* 
		PhysicsEngine::updateVelocitys(std::vector<ObjectType*> objects)

		iterates through each object in the vector,
		for each of these objects, iterate through each of its Velocities

		apply this Velocity to the object
		update this Velocity (decrement timeLeft counter and re-calculate strength)
		check to see if this Velocity has no timeLeft, if so erase it from that object
	*/
	void updateVelocities(std::vector<RectObject*> objects);

	void triggerImpact(RectObject* A, RectObject* B);

	void checkScreenBounds(RectObject* object);


	int screenWidth;
	int screenHeight;
};


#endif

