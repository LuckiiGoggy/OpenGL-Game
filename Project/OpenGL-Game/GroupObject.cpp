#include "GroupObject.h"


GroupObject::GroupObject()
{
}


GroupObject::~GroupObject()
{
}


GroupObject *GroupObject::AddChild(IGameObject *game){
	children.push_back(game);

	return this;
}

void GroupObject::Render()
{
	for (int i = 0; i < children.size(); i++){
		if (((IRenderable *)children[i])->IsVisible()) ((IRenderable *)children[i])->Render();
	}
}

void GroupObject::Move(int x, int y, int z)
{
	for (int i = 0; i < children.size(); i++){
		if (((IMovable *)children[i])->CanMove()) ((IMovable *)children[i])->Move(x, y, z);
	}
}