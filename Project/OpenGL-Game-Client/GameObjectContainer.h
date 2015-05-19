#ifndef GAMEOBJECTCONTAINER_H
#define GAMEOBJECTCONTAINER_H

#include <map>
#include <string>

#include "IGameObject.h"
#include "Transform.h"
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

	IGameObject *GetMember(std::string name);

protected:
	virtual void MoveMembers(glm::vec3);
	virtual void MoveMembers(float x, float y, float z);
	virtual void RenderMembers(void);
	virtual void UpdateMembers(float timeDelta);
	virtual void RotateMembers(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint = glm::vec3(0.0f), Transform::Space transformSpace = Transform::Space::Local);


	void UpdateMember(std::string, float timeDelta);
	void MoveToMembers(glm::vec3 moveDelta);
	virtual void RotateMembersTo(glm::mat4 &rot);

};

#endif