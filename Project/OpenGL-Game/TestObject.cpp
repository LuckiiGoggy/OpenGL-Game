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

void TestObject::Move(int x, int y, int z)
{

#ifdef DEBUG
	std::cout << "\nTestObject Moving...";
	std::cout << " x: " << x;
	std::cout << " y: " << y;
	std::cout << " z: " << z;
#endif
}