//Santo Tallarico COMP4900 World Builder/Editor
#ifndef _WORLDENGINE_H_
#define _WORLDENGINE_H_

//#define NDEBUG
#define FREEGLUT_LIB_PRAGMAS 0

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "WorldSquare.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class WorldEngine {

public:
	std::vector<WorldSquare> squares;
	float w;
	float h;

	WorldEngine();
	void writeWorld();
	void readWorld();
};

#endif
