#include "TestObject.h"
#include <iostream>



TestObject::TestObject()
{
	isVisible = true;
	canMove = true;
}


TestObject::~TestObject()
{
}

void TestObject::Render(){
#ifdef DEBUG
	std::cout << "\nTestObject Rendering...";
#endif
}

void TestObject::Move(glm::vec3 moveDelta)
{

#ifdef DEBUG
	std::cout << "\nTestObject Moving...";
	std::cout << " x: " << moveDelta.x;
	std::cout << " y: " << moveDelta.y;
	std::cout << " z: " << moveDelta.z;
#endif
}