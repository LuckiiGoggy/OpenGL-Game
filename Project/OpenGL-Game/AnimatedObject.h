#pragma once
#include "Transform.h"
#include "IGameObject.h"
#include "IRenderable.h"
#include "GameObjectContainer.h"

class AnimatedObject : public IGameObject, public Transform, public IRenderable, public GameObjectContainer
{
public:
	AnimatedObject();
	~AnimatedObject();
	void Update();
};

