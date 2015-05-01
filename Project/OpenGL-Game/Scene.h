#ifndef SCENE_H
#define SCENE_H

#include "IUpdateable.h"
#include "IGameObject.h"
#include "GameObjectContainer.h"

class Scene : public GameObjectContainer, public IGameObject, public IUpdateable
{
public:
	Scene();
	~Scene();

	virtual void Init(void);

	virtual void Update(float timeDelta);
	void Render(void);
};

#endif