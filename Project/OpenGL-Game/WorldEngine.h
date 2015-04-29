#ifndef _WORLDENGINE_H_
#define _WORLDENGINE_H_

#include "openGL.h"
#include "WorldSquare.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Dependencies\dirent\dirent.h"
#include "InputManager.h"

class WorldEngine {

public:
	std::vector<WorldSquare> squares;
	std::vector<std::string> levelNames;
	std::string filetype;
	std::string path;
	int height;
	int width;
	int w;
	int h;
	int currentsectionx;
	int currentsectiony;

	bool loaded;

	WorldEngine(int WIDTH, int HEIGHT);
	void loadDirectory();
	void readWorld(std::string filename);
	bool writeWorld(std::string filename);
	bool newWorld(std::string filename, std::string sW, std::string sH);
	void renderWorld();
	void updateSquare(Point p, int type);
};

#endif
