#ifndef GROUPOBJECT_H
#define GROUPOBJECT_H

#include "Dependencies\glm\glm\glm.hpp"
#include "IGameObject.h"
#include "IMovable.h"
#include "IUpdateable.h"

#include "Position.h"
#include <map>
#include <string>



/** A Group Object is a group of Game Objects that move as one entity **/
class GroupObject : public IMovable, public IGameObject
{
public:
	GroupObject();
	~GroupObject();

	/**Add a GameObject into members
		@param name - name key index of the member added
		@param obj  - pointer to the member added
		**/
	GroupObject *AddMember(std::string name, IGameObject *obj);
	/**Remove a GameObject from members
		@param name - name key index of the member to be removed 
		**/
	GroupObject *RemoveMember(std::string name);

	/**Render function of the Group Object(renders members)**/
	void Render();
	/**Moves the GroupObject and all its members**/
	void Move(glm::vec3);


protected:
	/**Moves the members of the GroupObject that can move**/
	void MoveMembers(glm::vec3 moveDelta);
	std::map<std::string, IGameObject *> members;
	glm::vec3 position;
};

#endif