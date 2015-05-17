#include "GameObjectContainer.h"

#include "IUpdateable.h"
#include "IRenderable.h"
#include "IMovable.h"

#include <iostream>
#include "Transform.h"

//#define DEBUG

GameObjectContainer::GameObjectContainer()
{
}


GameObjectContainer::~GameObjectContainer()
{
// 	std::map<std::string, IGameObject *>::iterator iter;
// 
// 	for (iter = members.begin(); iter != members.end(); ++iter) {
// 		delete iter->second;
// 	}
// 	members.empty();
}

void GameObjectContainer::AddMember(std::string name, IGameObject *game){
	this->members[name] = game;
	
}

void GameObjectContainer::RemoveMember(std::string name){
	delete members[name];
	members.erase(name);
	
}

void GameObjectContainer::EmptyMembers(void){
	std::map<std::string, IGameObject *>::iterator iter;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		delete iter->second;
	}
	members.empty();
	
}

void GameObjectContainer::MoveMembers(glm::vec3 moveDelta){
	std::map<std::string, IGameObject *>::iterator iter;
	Transform *moveable;
	
	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		moveable = dynamic_cast<Transform*>(iter->second);
		if (moveable != 0){
			moveable->Move(moveDelta, Transform::Space::Local);
		}
	}

}
void GameObjectContainer::MoveMembers(float x, float y, float z){
	std::map<std::string, IGameObject *>::iterator iter;
	Transform *moveable;

	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		moveable = dynamic_cast<Transform*>(iter->second);
		if (moveable != 0){
			moveable->Move(glm::vec3(x, y, z), Transform::Space::Local);
		}
	}

}



void GameObjectContainer::RotateMembers(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint, Transform::Space transformSpace){
	std::map<std::string, IGameObject *>::iterator iter;
	Transform *transformable;

	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		transformable = dynamic_cast<Transform*>(iter->second);
		if (transformable != 0){
			transformable->Rotate(axisX, axisY, axisZ, angle, rotPoint, transformSpace);
		}
	}
}

void GameObjectContainer::RenderMembers(void)
{
	std::map<std::string, IGameObject *>::iterator iter;
	IRenderable *renderable;

	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		renderable = dynamic_cast<IRenderable*>(iter->second);
		if (renderable != 0){
			renderable->Render();
		}
	}

}


void GameObjectContainer::UpdateMember(std::string key, float timeDelta)
{
	IUpdateable *updateable = dynamic_cast<IUpdateable *>(members[key]);

	if (updateable != 0){
		updateable->Update(timeDelta);
	}
}

void GameObjectContainer::UpdateMembers(float timeDelta)
{
	std::map<std::string, IGameObject *>::iterator iter;
	IUpdateable *updateable = 0;

	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		updateable = dynamic_cast<IUpdateable *>(iter->second);

		if (updateable != 0){
			updateable->Update(timeDelta);
		}
	}

}

IGameObject * GameObjectContainer::GetMember(std::string name){
	return members[name];
}