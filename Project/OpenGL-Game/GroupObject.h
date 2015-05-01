#ifndef GROUPOBJECT_H
#define GROUPOBJECT_H

#include "Dependencies\glm\glm\glm.hpp"
#include "IGameObject.h"
#include "IMovable.h"
#include "IUpdateable.h"
#include "GameObjectContainer.h"

#include "Position.h"
#include <map>
#include <string>



/** A Group Object is a group of Game Objects that move as one entity **/
class GroupObject : public GameObjectContainer, public IMovable, public IGameObject, public IUpdateable
{
public:
	GroupObject();
	~GroupObject();

	/**Render function of the Group Object(renders members)**/
	void Render();
	/**Moves the GroupObject and all its members**/
	void Move(glm::vec3);

	void Update(float timeDelta);


protected:

	glm::vec3 position;
};

#endif