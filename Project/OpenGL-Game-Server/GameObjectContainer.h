#ifndef GAMEOBJECTCONTAINER_H
#define GAMEOBJECTCONTAINER_H

#include <map>
#include <string>

#include "IGameObject.h"
#include "Transform.h"
#include "Dependencies\glm\glm\glm.hpp"
#include <vector>

class GameObjectContainer
{
public:
	GameObjectContainer();
	~GameObjectContainer();

	/**Add a GameObject into members
	@param name - name key index of the member added
	@param obj  - pointer to the member added
	**/
	virtual void AddMember(int, IGameObject *obj);

	/**Remove a GameObject from members
	@param name - name key index of the member to be removed
	**/
	virtual void RemoveMember(int name);
	virtual std::map<int, IGameObject*>::iterator RemoveMember(std::map<int, IGameObject*>::iterator it);

	/**Removes all GameObjects from members**/
	virtual void EmptyMembers(void);

	std::map<int, IGameObject *> members;

	IGameObject *GetMember(int name);


	virtual void MoveMembers(glm::vec3);
	virtual void MoveMembers(float x, float y, float z);
	virtual void UpdateMembers(float timeDelta);
	virtual void RotateMembers(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint = glm::vec3(0.0f), Transform::Space transformSpace = Transform::Space::Local);
	void UpdateMember(int, float timeDelta);
	std::vector<IGameObject *> GetMembers();

protected:

};

#endif