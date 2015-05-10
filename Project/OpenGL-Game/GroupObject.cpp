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

void GroupObject::Move(float dX, float dY, float dZ, Space transformSpace)
{
	glm::vec3 moveDelta = glm::vec3(dX, dY, dZ);
	Transform::Move(moveDelta, transformSpace);
	MoveMembers(moveDelta);
}

void GroupObject::Move(glm::vec3 moveDelta, Space transformSpace)
{
	Transform::Move(moveDelta, transformSpace);
	MoveMembers(moveDelta);
}


void GroupObject::Rotate(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint, Space transformSpace){
	switch (transformSpace)
	{
	case Transform::Local:
		Transform::Rotate(axisX, axisY, axisZ, angle);
		RotateMembers(axisX, axisY, axisZ, angle, position, Transform::Global);
		break;
	case Transform::Global:
		Transform::Rotate(axisX, axisY, axisZ, angle, position, transformSpace);
		RotateMembers(axisX, axisY, axisZ, angle, position, transformSpace);
		break;
	default:
		break;
	}
}