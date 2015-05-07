#include "GroupObject.h"
#include <iostream>
#include <typeinfo>


GroupObject::GroupObject()
{
}

GroupObject::~GroupObject()
{
	EmptyMembers();
}

void GroupObject::Render()
{
	#ifdef DEBUG
		std::cout << "\nGroup Object Rendering..";
	#endif
	
	RenderMembers();

}

void GroupObject::Update(float timeDelta){
	UpdateMembers(timeDelta);
}

void GroupObject::Move(glm::vec3 moveDelta)
{
#ifdef DEBUG
	std::cout << "\nGroup Object Moving..";
	std::cout << "(x: " << moveDelta.x;
	std::cout << ", y: ";
	std::cout << y << ", z: ";
	std::cout << z << ")";
#endif
	position += moveDelta;

	MoveMembers(moveDelta);
}


void GroupObject::RotateY(float angle)
{

}
