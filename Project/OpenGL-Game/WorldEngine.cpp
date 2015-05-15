#include "WorldEngine.h"
#include "MeshObject.h"
#include "GlutManager.h"

char* floor_filename = (char*) "../Assets/Models/floorPlane.obj";
char* wall_filename = (char*) "../Assets/Models/wallCube.obj";
char* v_wall_filename = (char*) "../Assets/Shaders/new-shading.v.glsl";
char* f_wall_filename = (char*) "../Assets/Shaders/new-shading.f.glsl";
char* v_floor_filename = (char*) "../Assets/Shaders/floor-shading.v.glsl";
char* f_floor_filename = (char*) "../Assets/Shaders/floor-shading.f.glsl";
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
	wall->Init(wall_filename, v_wall_filename, f_wall_filename);
	floor->Init(floor_filename, v_floor_filename, f_floor_filename);

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
				squares.push_back(WorldSquare((int)j, (int)i, block));
				MeshObject* p;
				switch (block) {
				case WALL:
				{
					p = new MeshObject(*wall);
					p->Move(glm::vec3(j * tileLength, 3.0f, i * tileLength));
					tileNo++;
					std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);
					break;
				}
				case FLOOR:
				{
					p = new MeshObject(*floor);
					p->Move(glm::vec3(j * tileLength, -1.0f, i * tileLength));
					tileNo++;
					/*std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);*/
					break;
				}
				case MOVEWALL:
				{
					p = new MeshObject(*floor);
					p->Move(glm::vec3(j * tileLength, -1.0f, i * tileLength));
					/*std::string name = "extrafloor" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);*/
					meshes.push_back(p);

					p = new MeshObject(*wall);
					p->Move(glm::vec3(j * tileLength, 3.0f, i * tileLength));
					tileNo++;
					std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 3, tileNo);
					
					break;
				}
				case SPAWN:
				{
					p = new MeshObject(*floor);
					p->Move(glm::vec3(j * tileLength, -1.0f, i * tileLength));
					tileNo++;
					/*std::string name = "tile" + std::to_string(tileNo);
					GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);*/
					break;
				}
				default:
				{
					p = new MeshObject(*wall);
					p->Move(glm::vec3(j * tileLength, 3.0f, i * tileLength));
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
	for (size_t i = 0; i < meshes.size(); i++) {
		meshes[i]->Update(0.0);
		meshes[i]->Render();
	}
}
