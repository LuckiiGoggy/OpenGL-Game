
#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
	screenWidth = 400;
	screenHeight = 400;
}
PhysicsEngine::PhysicsEngine(int screenWidth_, int screenHeight_)
{
	screenWidth = screenWidth_;
	screenHeight = screenHeight_;
}
void PhysicsEngine::applyVelocity(RectObject* object, Velocity f)
{
	object->move(
		(int)( (f.strength) * (f.x) ),
		(int)( (f.strength) * (f.y) )
		);
}
void PhysicsEngine::applyVelocity(RectObject* object, Velocity* f)
{
	object->move(
		(int)( (f->strength) * (f->x) ),
		(int)( (f->strength) * (f->y) )
		);
}
void PhysicsEngine::applyVelocity(RectObject* object, float x_, float y_, float z_, int type_, int duration_ /* = 10 */)
{
	Velocity* f = new Velocity(x_, y_, z_, type_, duration_);
	object->addVelocity(f);
	object->move(
		(int)( (f->strength) * (f->x) ),
		(int)( (f->strength) * (f->y) )
		);
}
void PhysicsEngine::triggerImpact(RectObject* A, RectObject* B)
{
	int numOfVelocities_A = A->velocities.size();
	int numOfVelocities_B = B->velocities.size();

	//A->velocities.clear();
	//B->velocities.clear();

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
	xImpact_A = xTotal_A * A->mass;
	yImpact_A = yTotal_A * A->mass;
	zImpact_A = zTotal_A * A->mass;

	xImpact_B = xTotal_B * B->mass;
	yImpact_B = yTotal_B * B->mass;
	zImpact_B = zTotal_B * B->mass;

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
	float xIntersect = std::max(0, ( std::max(A->ex, B->ex) - std::min(A->sx, B->sx) ) );
	float yIntersect = std::max(0, ( std::max(A->ey, B->ey) - std::min(A->sy, B->sy) ) );
	float xOverlap = (A->ex - A->sx) + (B->ex - B->sx) - xIntersect;
	float yOverlap = (A->ey - A->sy) + (B->ey - B->sy) - yIntersect;
	
	if (impact_From_A->y > impact_From_B->y)
	{
		//if A is pushing B down more than B is pushing A down
		//Move B down and A up
		A->move(0, -yOverlap);
		B->move(0, yOverlap);
	}
	else if (impact_From_A->y < impact_From_B->y)
	{
		//if B is pushing A down more than A is pushing B down
		//Move A down and B up
		A->move(0, yOverlap);
		B->move(0, -yOverlap);
	}
	/*else
	{
		//if they are the same, then you have to calculate which one is on either side
		if (A->sy > B->sy)
		{
			//if A is lower than B
			//Move A down and B up
			A->move(0, yOverlap);
			B->move(0, -yOverlap);
		}
		else if (A->sy < B->sy)
		{
			//if B is lower than A
			//Move B down and A up
			A->move(0, -yOverlap);
			B->move(0, yOverlap);
		}
		else
		{
			//if they perfectly overlap in the Y, move B down and A up
			A->move(0, -yOverlap);
			B->move(0, yOverlap);
		}
	}//*/

	if (impact_From_A->x > impact_From_B->x)
	{
		//if A is pushing B right more than B is pushing A right
		//Move B right and A left
		A->move(-xOverlap, 0);
		B->move(xOverlap, 0);
	}
	else if (impact_From_A->x < impact_From_B->x)
	{
		//if B is pushing A right more than A is pushing B right
		//Move A right and B left
		A->move(xOverlap, 0);
		B->move(-xOverlap, 0);
	}
	/*else
	{
		//if they are the same, then you have to calculate which one is on either side
		if (A->sx > B->sx)
		{
			//if A is more to the Right than B
			//Move A right and B left
			A->move(xOverlap, 0);
			B->move(-xOverlap, 0);
		}
		else if (A->sx < B->sx)
		{
			//if B is more to the Right than A
			//Move B right and A left
			A->move(-xOverlap, 0);
			B->move(xOverlap, 0);
		}
		else
		{
			//if they perfectly overlap in the X, move B right and A left
			A->move(-xOverlap, 0);
			B->move(xOverlap, 0);
		}
	}//*/

	if (impact_From_B == impact_From_A)
	{
		//if they are the same, then you have to calculate which one is on either side
		if (A->sy > B->sy)
		{
			//if A is lower than B
			//Move A down and B up
			A->move(0, yOverlap);
			B->move(0, -yOverlap);
		}
		else if (A->sy < B->sy)
		{
			//if B is lower than A
			//Move B down and A up
			A->move(0, -yOverlap);
			B->move(0, yOverlap);
		}
		else
		{
			//if they perfectly overlap in the Y, move B down and A up
			A->move(0, -yOverlap);
			B->move(0, yOverlap);
		}

		//if they are the same, then you have to calculate which one is on either side
		if (A->sx > B->sx)
		{
			//if A is more to the Right than B
			//Move A right and B left
			A->move(xOverlap, 0);
			B->move(-xOverlap, 0);
		}
		else if (A->sx < B->sx)
		{
			//if B is more to the Right than A
			//Move B right and A left
			A->move(-xOverlap, 0);
			B->move(xOverlap, 0);
		}
		else
		{
			//if they perfectly overlap in the X, move B right and A left
			A->move(-xOverlap, 0);
			B->move(xOverlap, 0);
		}
	}


	//Remove all forces related to projectiles. Projectiles are destroyed on impact
	for (int i = 0; i < numOfVelocities_A; i++)
	{
		if (A->velocities[i]->velocityType == 1)
		{
			A->velocities.erase(A->velocities.begin() + i);
		}
	}
	for (int i = 0; i < numOfVelocities_B; i++)
	{
		if (B->velocities[i]->velocityType == 1)
		{
			B->velocities.erase(B->velocities.begin() + i);
		}
	}

	A->addVelocity(impact_From_B);
	B->addVelocity(impact_From_A);

}
/* 
	PhysicsEngine::updateVelocitys(std::vector<ObjectType*> objects)

	iterates through each object in the vector,
	for each of these objects, iterate through each of its Velocitys

	apply this Velocity to the object
	update this Velocity (decrement timeLeft counter and re-calculate strength)
	check to see if this Velocity has no timeLeft, if so erase it from that object
*/
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
					(int)( (curVelocity) * (objects[i]->velocities[j]->x) ),
					(int)( (curVelocity) * (objects[i]->velocities[j]->y) )
					//(int)( (curVelocity) * (objects[i]->Velocitys[j]->z) )
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