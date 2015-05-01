#include "GameObjectContainer.h"

#include "IUpdateable.h"
#include "IRenderable.h"
#include "IMovable.h"

GameObjectContainer::GameObjectContainer()
{
}


GameObjectContainer::~GameObjectContainer()
{
	std::map<std::string, IGameObject *>::iterator iter;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		delete iter->second;
	}
	members.empty();
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
	IMovable *moveable;
	
	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		moveable = dynamic_cast<IMovable*>(iter->second);
		if (moveable != 0 && moveable->CanMove()){
			#ifdef DEBUG
			std::cout << "\n\tMoving Member: " << iter->first;
			#endif
			moveable->Move(moveDelta);
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
			#ifdef DEBUG
				std::cout << "\n\tRendering Member: " << iter->first;
			#endif
			renderable->Render();
		}
	}

}

void GameObjectContainer::UpdateMembers(float timeDelta)
{
	std::map<std::string, IGameObject *>::iterator iter;
	IUpdateable *updateable = 0;

	for (iter = this->members.begin(); iter != this->members.end(); ++iter) {
		updateable = dynamic_cast<IUpdateable *>(iter->second);

		if (updateable != 0){
			#ifdef DEBUG
				std::cout << "\n\tUpdating Member: " << iter->first;
			#endif
			updateable->Update(timeDelta);
		}
	}

}