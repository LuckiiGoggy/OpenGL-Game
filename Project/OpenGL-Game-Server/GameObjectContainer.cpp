#include "GameObjectContainer.h"

#include "IUpdateable.h"
#include "IMovable.h"

#include <iostream>
#include "Transform.h"

//#define DEBUG

GameObjectContainer::GameObjectContainer()
{
}


GameObjectContainer::~GameObjectContainer()
{
// 	std::map<int, IGameObject *>::iterator iter;
// 
// 	for (iter = members.begin(); iter != members.end(); ++iter) {
// 		delete iter->second;
// 	}
// 	members.empty();
}

void GameObjectContainer::AddMember(int key, IGameObject *game){
	this->members[key] = game;

	Transform *transformable = dynamic_cast<Transform *>(game);

	if (transformable != 0){
		transformable->SetObjectId(key);
	}
	
}

void GameObjectContainer::RemoveMember(int key){
/*	delete members[key];*/
	members.erase(key);
	
}

std::map<int, IGameObject*>::iterator GameObjectContainer::RemoveMember(std::map<int, IGameObject*>::iterator it)
{
	return members.erase(it);
}

void GameObjectContainer::EmptyMembers(void){
	std::map<int, IGameObject *>::iterator iter;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		delete iter->second;
	}
	members.empty();
	
}

void GameObjectContainer::MoveMembers(glm::vec3 moveDelta){
	std::map<int, IGameObject *>::iterator iter;
	Transform *moveable;
	
	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		moveable = dynamic_cast<Transform*>(iter->second);
		if (moveable != 0){
			moveable->Move(moveDelta, Transform::Space::Local);
		}
	}

}
void GameObjectContainer::MoveMembers(float x, float y, float z){
	std::map<int, IGameObject *>::iterator iter;
	Transform *moveable;

	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		moveable = dynamic_cast<Transform*>(iter->second);
		if (moveable != 0){
			moveable->Move(glm::vec3(x, y, z), Transform::Space::Local);
		}
	}

}



void GameObjectContainer::RotateMembers(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint, Transform::Space transformSpace){
	std::map<int, IGameObject *>::iterator iter;
	Transform *transformable;

	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		transformable = dynamic_cast<Transform*>(iter->second);
		if (transformable != 0){
			transformable->Rotate(axisX, axisY, axisZ, angle, rotPoint, transformSpace);
		}
	}
}


void GameObjectContainer::UpdateMember(int key, float timeDelta)
{
	IUpdateable *updateable = dynamic_cast<IUpdateable *>(members[key]);

	if (updateable != 0){
		updateable->Update(timeDelta);
	}
}

void GameObjectContainer::UpdateMembers(float timeDelta)
{
	std::map<int, IGameObject *>::iterator iter;
	IUpdateable *updateable = 0;
	Transform *transformable;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		updateable = dynamic_cast<IUpdateable *>(iter->second);
		transformable = dynamic_cast<Transform*>(iter->second);

		if (updateable != 0){
			updateable->Update(timeDelta);
		}
		if (transformable != 0){
			transformable->UpdatePacket();
		}
	}

}

IGameObject * GameObjectContainer::GetMember(int key){
	return members[key];
}

std::vector<IGameObject*> GameObjectContainer::GetMembers(){
	std::vector<IGameObject*> v;

	for (std::map<int, IGameObject *>::iterator it = members.begin(); it != members.end(); ++it) {
		v.push_back(it->second);
	}

	return v;
}