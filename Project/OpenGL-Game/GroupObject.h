#ifndef GROUPOBJECT_H
#define GROUPOBJECT_H

#pragma once
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
	void Move(int x, int y, int z);


protected:
	/**Moves the members of the GroupObject that can move**/
	void MoveMembers(int x, int y, int z);
	std::map<std::string, IGameObject *> members;
	Position3D position;
};

#endif