#include "WorldEngine.h"
#include "MeshObject.h"
#include "GlutManager.h"

char* floor_filename = (char*) "../Assets/Models/floorPlane.obj";
char* wall_filename = (char*) "../Assets/Models/wallCube.obj";
char* v_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.v.glsl";
char* f_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.f.glsl";
float tileLength = 8;
int tileNo = 0;

WorldEngine::WorldEngine() {
	loaded = false;
	filetype = ".lvl";
	path = "../Assets/Levels/";
	wall = new MeshObject();
	floor = new MeshObject();
}

void WorldEngine::loadDirectory() {
	DIR *dir;
	struct dirent *ent;
	char* temp;
	if ((dir = opendir("../Assets/Levels")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_namlen > filetype.size()) {
				if (filetype.compare(0, filetype.size(), ent->d_name,
					ent->d_namlen - filetype.size(), filetype.size()) == 0) {
					levelNames.push_back(strtok_s(ent->d_name, ".", &temp));
				}
			}
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
		return;
	}
}

void WorldEngine::readWorld(std::string filename) {
	std::ifstream file;
	file.open(path + filename + filetype);
	wall->Init(wall_filename, v_shader_filename, f_shader_filename);
	floor->Init(floor_filename, v_shader_filename, f_shader_filename);

	if (file.is_open()) {
		int index;
		int block;
		std::string s;
		squares.clear();
		meshes.clear();
		tileNo = 0;

		std::getline(file, s);
		w = stoi(s);
		std::getline(file, s);
		h = stoi(s);

		glMatrixMode(GL_PROJECTION);		// setup viewing projection
		glLoadIdentity();					// start with identity matrix
		glOrtho(-w, w, -h, h, -h, h);	// setup a wxhx2h viewing world

		for (float i = 0; i < h; i++) {
			std::getline(file, s);
			index = 0;
			for (float j = 0; j < w; j++) {
				block = (int)(s.at(index) - '0');
				squares.push_back(WorldSquare((int)i, (int)j, block));
				MeshObject* p;
				switch (block) {
				case WALL:
				{
					p = new MeshObject(*wall);
					p->Move(glm::vec3(j * tileLength, 1.0f, i * tileLength));
					tileNo++;
					std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);
					break;
				}
				case FLOOR:
				{
					p = new MeshObject(*floor);
					p->Move(glm::vec3(j * tileLength, 0.0f, i * tileLength));
					tileNo++;
					std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);
					break;
				}
				case MOVEWALL:
				{
					p = new MeshObject(*wall);
					p->Move(glm::vec3(j * tileLength, 1.0f, i * tileLength));
					tileNo++;
					std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 3, tileNo);
					p = new MeshObject(*floor);
					p->Move(glm::vec3(j * tileLength, 0.0f, i * tileLength));
					name = "extrafloor" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);
					break;
				}
				case SPAWN:
				{
					p = new MeshObject(*floor);
					p->Move(glm::vec3(j * tileLength, 0.0f, i * tileLength));
					tileNo++;
					std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);
					break;
				}
				default:
				{
					p = new MeshObject(*wall);
					p->Move(glm::vec3(j * tileLength, 1.0f, i * tileLength));
					tileNo++;
					std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);
					break;
				}
				}
				meshes.push_back(p);
				index++;
			}
		}
		loaded = true;
		file.close();
	}
}

void WorldEngine::renderWorld() {
	int index = 0;
	int block;

	for (float i = 0; i < h; i++) {
		for (float j = 0; j < w; j++) {
			block = squares.at(index).type;
			meshes[index]->Update(0.0);
			meshes[index]->Render();
			index++;			
		}
	}
}
