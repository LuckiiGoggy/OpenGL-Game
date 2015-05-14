#ifndef OVERLAY_H
#define OVERLAY_H
#pragma once
#include "openGL.h"
#include "windows.h"

class Overlay2D
{
public:
	Overlay2D();
	~Overlay2D();
	void prepare2D(int, int, int, int);
	void Render();
	void unprepare2D();

	void increaseAmmo();
	void decreaseAmmo();
	void increaseHP();
	void decreaseHP();
	void increaseScore();
	void decreaseScore();
	void setAmmo(int);
	void setHP(int);
	void setScore(int);

	int getAmmo() { return ammo; }
	int getHP() { return health; }
	int getScore() { return score; }

private:
	int health, ammo, score;
};

#endif