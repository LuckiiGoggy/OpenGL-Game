#ifndef GAMEOBJECTCONTAINER_H
#define GAMEOBJECTCONTAINER_H

#include <map>
#include <string>

#include "IGameObject.h"
#include "Dependencies\glm\glm\glm.hpp"

class GameObjectContainer
{
public:
	GameObjectContainer();
	~GameObjectContainer();

	/**Add a GameObject into members
	@param name - name key index of the member added
	@param obj  - pointer to the member added
	**/
	virtual void AddMember(std::string name, IGameObject *obj);

	/**Remove a GameObject from members
	@param name - name key index of the member to be removed
	**/
	virtual void RemoveMember(std::string name);

	/**Removes all GameObjects from members**/
	virtual void EmptyMembers(void);

	std::map<std::string, IGameObject *> members;


protected:
	virtual void MoveMembers(glm::vec3);
	virtual void RenderMembers(void);
	virtual void UpdateMembers(float timeDelta);


};

#endif