#pragma once
#include "GameObject.h"
#include "Movable.h"
#include "Renderable.h"
#include "Position.h"
#include <vector>

/** A Group Object is a group of Game Objects that move as one entity **/
class GroupObject: public Movable, public Renderable
{
public:
	GroupObject();
	~GroupObject();


	void Render();
	void Move(int x, int y, int z);
	void MoveUp(int delta);
	void MoveDown(int delta);
	void MoveLeft(int delta);
	void MoveRight(int delta);
	void MoveForward(int delta);
	void MoveBackward(int delta);


protected:
	std::vector<GameObject *> children;
	Position3D position;
};

