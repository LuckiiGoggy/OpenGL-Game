#include "WorldEngine.h"

const int WALL = 0;
const int FLOOR = 1;
const int MOVEWALL = 2;

WorldEngine::WorldEngine(int WIDTH, int HEIGHT) {
	loaded = false;
	filetype = ".lvl";
	path = "../Assets/Levels/";
	width = WIDTH;
	height = HEIGHT;
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

		std::getline(file, s);
		w = stoi(s);
		std::getline(file, s);
		h = stoi(s);

		glMatrixMode(GL_PROJECTION);		// setup viewing projection
		glLoadIdentity();					// start with identity matrix
		glOrtho(0.0, w, 0.0, h, -1.0, 1.0);	// setup a wxhx2 viewing world

		for (float i = 0; i < h; i++) {
			std::getline(file, s);
			index = 0;
			for (float j = 0; j < w; j++) {
				block = (int)(s.at(index) - '0');
				squares.push_back(WorldSquare((int)i, (int)j, block));
				index++;
			}
		}

		loaded = true;
		file.close();
	}
}

bool WorldEngine::writeWorld(std::string filename) {
	std::ofstream file;
	file.open(path + filename + filetype, std::ofstream::trunc);

	if (file.is_open()) {
		file << w << std::endl;
		file << h << std::endl;
		for (std::vector<int>::size_type i = 0; i != squares.size(); i++) {
			if (i % w == 0 && i != 0) {
				file << std::endl;
			}
			file << squares.at(i).type;
		}

		file.close();
	}
	for (int j = 0; j < levelNames.size(); j++) {
		if (filename.compare(levelNames[j].substr(0, levelNames[j].find("."))) == 0) {
			return true;
		}
	}
	levelNames.push_back(filename);
	return false;
}

void WorldEngine::renderWorld() {
	int index = 0;
	int block;
	for (float i = 0; i < h; i++) {
		for (float j = 0; j < w; j++) {
			block = squares.at(index).type;
			index++;
			switch (block) {
			case WALL:
			{
				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glVertex3f(i, j, 0.0);
				glVertex3f(i + 1.0f, j, 0.0);
				glVertex3f(i + 1.0f, j + 1.0f, 0.0);
				glVertex3f(i, j + 1.0f, 0.0);
				glEnd();
				glFlush();
				break;
			}
			case FLOOR:
			{
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glVertex3f(i, j, 0.0);
				glVertex3f(i + 1.0f, j, 0.0);
				glVertex3f(i + 1.0f, j + 1.0f, 0.0);
				glVertex3f(i, j + 1.0f, 0.0);
				glEnd();
				glFlush();
				break;
			}
			case MOVEWALL:
			{
				glColor3f(0.0, 1.0, 1.0);
				glBegin(GL_POLYGON);
				glVertex3f(i, j, 0.0);
				glVertex3f(i + 1.0f, j, 0.0);
				glVertex3f(i + 1.0f, j + 1.0f, 0.0);
				glVertex3f(i, j + 1.0f, 0.0);
				glEnd();
				glFlush();
				break;
			}
			default:
			{
				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
				glVertex3f(i, j, 0.0);
				glVertex3f(i + 1.0f, j, 0.0);
				glVertex3f(i + 1.0f, j + 1.0f, 0.0);
				glVertex3f(i, j + 1.0f, 0.0);
				glEnd();
				glFlush();
				break;
			}
			}
		}
	}
}

void WorldEngine::updateSquare(Point p, int type) {
	currentsectionx = p.x / (width / w);
	currentsectiony = (height - p.y) / (height / h);
	squares[currentsectionx * h + currentsectiony].type = type;
}
