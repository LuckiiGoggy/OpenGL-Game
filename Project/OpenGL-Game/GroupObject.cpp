#include "GroupObject.h"


GroupObject::GroupObject()
{
}


GroupObject::~GroupObject()
{
}


GroupObject *GroupObject::AddChild(std::string name, IGameObject *game){
	children[name] = game;

	return this;
}

void GroupObject::Render()
{
	std::map<std::string, IGameObject *>::iterator iter;

	for (iter = children.begin(); iter != children.end(); ++iter) {
		if (((IRenderable *)iter->second)->IsVisible()) ((IRenderable *)iter->second)->Render();
	}
}

void GroupObject::Move(int x, int y, int z)
{
	std::map<std::string, IGameObject *>::iterator iter;

	for (iter = children.begin(); iter != children.end(); ++iter) {
		if (((IRenderable *)iter->second)->IsVisible()) ((IRenderable *)iter->second)->Render();
	}
}