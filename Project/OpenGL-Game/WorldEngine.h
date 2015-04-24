//Santo Tallarico COMP4900 World Builder/Editor
#ifndef _WORLDENGINE_H_
#define _WORLDENGINE_H_

#include "openGL.h"
#include "WorldSquare.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Dependencies\dirent\dirent.h"

class WorldEngine {

public:
	std::vector<WorldSquare> squares;
	std::vector<std::string> levelNames;
	std::string filetype;
	std::string path;
	float w;
	float h;
	bool loaded;

	WorldEngine();
	void writeWorld();
	void readWorld();
	void renderWorld();
};

#endif
