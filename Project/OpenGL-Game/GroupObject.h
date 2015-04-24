#ifndef GROUPOBJECT_H
#define GROUPOBJECT_H

#pragma once
#include "IGameObject.h"
#include "IMovable.h"
#include "IRenderable.h"
#include "Position.h"
#include <vector>
#include <map>
#include <string>

/** A Group Object is a group of Game Objects that move as one entity **/
class GroupObject: public IMovable, public IRenderable
{
public:
	GroupObject();
	~GroupObject();

	GroupObject *AddChild(std::string name, IGameObject *obj);

	void Render();
	void Move(int x, int y, int z);


protected:
	std::map<std::string, IGameObject *> children;
	Position3D position;
};

#endif