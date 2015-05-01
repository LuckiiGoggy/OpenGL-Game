
#include "Velocity.h"

Velocity::Velocity()
{
	x, y, z = 0.0f;
	isAlive = false;
}
Velocity::Velocity(float x_, float y_, float z_, int type_, int duration_ = 10)
{
	x = x_;
	y = y_;
	z = z_;

	velocityType = type_;
	duration = duration_;//default: 10 frames if not specified
	timeLeft = duration_;
	strength = 1;

	isAlive = true;

}
/* 
	Velocity::update() decrements the timeLeft counter, then
	recalculates the strength by taking timeLeft / duration

	This function should be called on every Velocity once per frame
*/
void Velocity::update()
{
	if (velocityType == 1)//projectiles never slow down
	{

	}
	else
	{
		timeLeft--;
		if (timeLeft > 0)
		{
			strength = (float)timeLeft / (float)duration;
		}
		else
		{
			strength = 0.0f;
			isAlive = false;
		}
	}
	
}
bool Velocity::isDead()
{
	return !isAlive;
}