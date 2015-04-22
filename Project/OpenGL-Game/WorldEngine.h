//Santo Tallarico COMP4900 World Builder/Editor
#ifndef _WORLDENGINE_H_
#define _WORLDENGINE_H_

#include "openGL.h"
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
