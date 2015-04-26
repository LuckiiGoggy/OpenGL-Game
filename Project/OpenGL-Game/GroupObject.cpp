#include "GroupObject.h"
#include <iostream>
#include <typeinfo>


GroupObject::GroupObject()
{
}

GroupObject::~GroupObject()
{
	std::map<std::string, IGameObject *>::iterator iter;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		#ifdef DEBUG
		std::cout << "\n\tDeleting " << iter->first;
		#endif
		delete iter->second;
	}
	members.empty();
}

GroupObject *GroupObject::AddMember(std::string name, IGameObject *game){
	members[name] = game;
	return this;
}

GroupObject *GroupObject::RemoveMember(std::string name){
	delete members[name];
	members.erase(name);
	return this;
}

void GroupObject::Render()
{
#ifdef DEBUG
	std::cout << "\nGroup Object Rendering..";
#endif
	
	std::map<std::string, IGameObject *>::iterator iter;
	IRenderable *renderable;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		renderable = dynamic_cast<IRenderable*>(iter->second);
		if (renderable != 0 && renderable->IsVisible()){
			#ifdef DEBUG
			std::cout << "\n\tGroup Object Rendering " << iter->first;
			#endif
			renderable->Render();
		}
	}
}

void GroupObject::Move(int x, int y, int z)
{
#ifdef DEBUG
	std::cout << "\nGroup Object Moving..";
	std::cout << "(x: " << x << ", y: " << y << ", z: " << z << ")";
#endif
	position.x += x;
	position.y += y;
	position.z += z;
}

void GroupObject::MoveMembers(int x, int y, int z){
	std::map<std::string, IGameObject *>::iterator iter;
	IMovable *moveable;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		moveable = dynamic_cast<IMovable*>(iter->second);
		if (moveable != 0 && moveable->CanMove()){
			#ifdef DEBUG
			std::cout << "\n\tGroup Object Moving " << iter->first;
			#endif
			moveable->Move(x, y, z);
		}
	}
}