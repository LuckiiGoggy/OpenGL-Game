#include "WorldEngine.h"
#include "MeshObject.h"
#include "ServerMain.h"
#include "BoundingBoxLibrary.h"

float tileLength = 8;
int tileNo = 0;

WorldEngine::WorldEngine() {
	loaded = false;
	filetype = ".lvl";
	path = "../Assets/Levels/";
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

	if (file.is_open()) {
		int index;
		int block;
		std::string s;
		squares.clear();
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
				Transform* p;
				switch (block) {
				case WALL:
				{
					int objId = ServerMain::GetNewObjectId();
					p = new Transform(objId);
					p->Move(glm::vec3(j * tileLength, 1.0f, i * tileLength));
					tileNo++;
					std::string name = "Wall" + std::to_string(objId);
					ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewWall(), p, name, 4);
					ServerMain::AddMember(ServerMain::Walls, objId, p);
					break;
				}
				case FLOOR:
				{
					int objId = ServerMain::GetNewObjectId();
					p = new Transform(objId);
					p->Move(glm::vec3(j * tileLength, -1.0f, i * tileLength));
					tileNo++;
					ServerMain::AddMember(ServerMain::Floors, objId, p);
					break;
				}
				case MOVEWALL:
				{
					int objId = ServerMain::GetNewObjectId();
					p = new Transform(objId);
					p->Move(glm::vec3(j * tileLength, 1.0f, i * tileLength));
					tileNo++;
					std::string name = "Wall" + std::to_string(objId);
					ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewWall(), p, name, 3);
					ServerMain::AddMember(ServerMain::Walls, objId, p);
					//GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 3, tileNo);
					objId = ServerMain::GetNewObjectId();
					p = new Transform(objId);
					p->Move(glm::vec3(j * tileLength, -1.0f, i * tileLength));
					tileNo++;
					ServerMain::AddMember(ServerMain::Floors, objId, p);
					//GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);
					break;
				}
				case SPAWN:
				{
					int objId = ServerMain::GetNewObjectId();
					p = new Transform(objId);
					p->Move(glm::vec3(j * tileLength, -1.0f, i * tileLength));
					tileNo++;
					ServerMain::AddMember(ServerMain::Floors, objId, p);
					break;
				}
				default:
				{
					int objId = ServerMain::GetNewObjectId();
					p = new Transform(objId);
					p->Move(glm::vec3(j * tileLength, 1.0f, i * tileLength));
					tileNo++;
					std::string name = "Wall" + std::to_string(objId);
					ServerMain::GetPhysEngi()->registerRigidBody(BoundingBoxLibrary::NewWall(), p, name, 3);
					ServerMain::AddMember(ServerMain::Walls, objId, p);
					//GlutManager::GetPhysEngi()->registerRigidBody(p, p, name, 4, tileNo);
					break;
				}
				}
				index++;
			}
		}
		loaded = true;
		file.close();
	}
}
