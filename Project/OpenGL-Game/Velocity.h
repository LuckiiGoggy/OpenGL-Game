

#ifndef VELOCITY_H
#define VELOCITY_H


class Velocity
{
public:
	Velocity();
	Velocity(float x_, float y_, float z_, int type_, int duration_);

	/* 
		Velocity::update() decrements the timeLeft counter, then
		recalculates the strength by taking timeLeft / duration

		This function should be called on every Velocity once per frame
	*/
	void update();
	bool isDead();
	
	float x;//amount of Velocity in the x direction
	float y;//amount of Velocity in the y direction
	float z;//amount of Velocity in the z direction

	int velocityType;//Projectile = 1; PlayerMovement = 2; Impact = 3;

	int duration;//Amount of frames Velocity is applied (After this time ends the Velocity becomes NULL);
	int timeLeft;//Number of frames left (Frames Left Alive);

	float strength;// timeLeft/duration Coeffectient for the attenuation of the Velocity over time (over frames)

	bool isAlive;

	/*
		You would multiply the 'strength' with the x,y,z Velocity values to simulate the Velocity losing
		strength over time. This way the objects with Velocities applied to them do not move "Jaggedly"
		ie helps simulate Velocity attenuation over time.
	
	*/
};


#endif
