#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#pragma once
#include "IGameObject.h"
#include "IMovable.h"

class TestObject : public IGameObject, public IMovable
{
public:
	TestObject();
	~TestObject();
	void Render();
	void Move(glm::vec3);
};

#endif 