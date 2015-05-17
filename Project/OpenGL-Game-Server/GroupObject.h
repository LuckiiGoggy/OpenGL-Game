#ifndef GROUPOBJECT_H
#define GROUPOBJECT_H

#include "Dependencies\glm\glm\glm.hpp"
#include "IGameObject.h"
#include "IMovable.h"
#include "IUpdateable.h"
#include "GameObjectContainer.h"

#include <map>
#include <string>
#include "Transform.h"



/** A Group Object is a group of Game Objects that move as one entity **/
class GroupObject : public GameObjectContainer, public Transform
{
public:
	GroupObject();
	~GroupObject();

	/**Moves the GroupObject and all its members**/
	virtual void Move(float dX, float dY, float dZ, Space transformSpace = Space::Global);
	virtual void Move(glm::vec3 moveDelta, Space transformSpace = Space::Global);
	virtual void Rotate(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint = glm::vec3(0.0f), Space transformSpace = Space::Local);

	void Update(float timeDelta);
};

#endif