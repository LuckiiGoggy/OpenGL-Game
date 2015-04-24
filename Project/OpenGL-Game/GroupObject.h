#pragma once
#include "IGameObject.h"
#include "IMovable.h"
#include "IRenderable.h"
#include "Position.h"
#include <vector>

/** A Group Object is a group of Game Objects that move as one entity **/
class GroupObject: public IMovable, public IRenderable
{
public:
	GroupObject();
	~GroupObject();

	GroupObject *AddChild(IGameObject *obj);

	void Render();
	void Move(int x, int y, int z);


protected:
	std::vector<IGameObject *> children;
	Position3D position;
};

