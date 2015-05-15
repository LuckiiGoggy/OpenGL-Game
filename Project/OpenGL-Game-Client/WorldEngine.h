#ifndef _WORLDENGINE_H_
#define _WORLDENGINE_H_

#include "openGL.h"
#include "WorldSquare.h"
#include "MeshObject.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Dependencies\dirent\dirent.h"
#include "InputManager.h"

class WorldEngine {

public:
	enum TileType{ WALL, FLOOR, MOVEWALL, SPAWN };
	std::vector<WorldSquare> squares;
	std::vector<MeshObject*> meshes;
	std::vector<std::string> levelNames;
	std::string filetype;
	std::string path;
	int w;
	int h;
	int currentsectionx;
	int currentsectiony;
	bool loaded;
	MeshObject* wall;
	MeshObject* floor;

	WorldEngine();
	void loadDirectory();
	void readWorld(std::string filename);
	void renderWorld();
};

#endif
