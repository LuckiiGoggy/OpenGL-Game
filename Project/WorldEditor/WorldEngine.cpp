#include "WorldEngine.h"

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

		std::getline(file, s);
		w = stoi(s);
		std::getline(file, s);
		h = stoi(s);

		glMatrixMode(GL_PROJECTION);		// setup viewing projection
		glLoadIdentity();					// start with identity matrix
		glOrtho(0.0, w, 0.0, h, -h, h);	// setup a wxhx2h viewing world

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
	if (!filename.empty()) {
		file.open(path + filename + filetype, std::ofstream::trunc);
	}

	if (file.is_open()) {
		file << w << std::endl;
		file << h << std::endl;
		for (std::vector<int>::size_type i = 0; i != squares.size(); i++) {
			if (i % w == 0 && i != 0) {
				file << std::endl;
			}
			file << squares.at(i).type;
		}

		for (unsigned int j = 0; j < levelNames.size(); j++) {
			if (filename.compare(levelNames[j].substr(0, levelNames[j].find("."))) == 0) {
				return false;
			}
		}
		levelNames.push_back(filename);

		file.close();
	}

	return true;
}

bool WorldEngine::newWorld(std::string filename, std::string sW, std::string sH) {
	std::ofstream file;

	if (!filename.empty() && !sW.empty() && !sH.empty()) {
		file.open(path + filename + filetype, std::ofstream::trunc);
	}

	if (file.is_open()) {
		int block;
		squares.clear();

		w = stoi(sW);
		h = stoi(sH);

		glMatrixMode(GL_PROJECTION);		// setup viewing projection
		glLoadIdentity();					// start with identity matrix
		glOrtho(0.0, w, 0.0, h, -h, h);	// setup a wxhx2h viewing world

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (i == 0 || j == 0 || i == h - 1 || j == w - 1) {
					block = WALL;
				}
				else {
					block = FLOOR;
				}
				squares.push_back(WorldSquare((int)i, (int)j, block));
			}
		}

		file << w << std::endl;
		file << h << std::endl;
		for (std::vector<int>::size_type k = 0; k != squares.size(); k++) {
			if (k % w == 0 && k != 0) {
				file << std::endl;
			}
			file << squares.at(k).type;
		}

		file.close();
		loaded = true;

		for (unsigned int j = 0; j < levelNames.size(); j++) {
			if (filename.compare(levelNames[j]) == 0) {
				return false;
			}
		}

		levelNames.push_back(filename);

		return true;
	}
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
				glColor3f(0.0f, 0.0f, 0.0f);
				glBegin(GL_POLYGON);
				glVertex3f(j, i, 0.0f);
				glVertex3f(j + 1.0f, i, 0.0f);
				glVertex3f(j + 1.0f, i + 1.0f, 0.0f);
				glVertex3f(j, i + 1.0f, 0.0f);
				glEnd();
				glFlush();
				break;
			}
			case FLOOR:
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glBegin(GL_POLYGON);
				glVertex3f(j, i, 0.0f);
				glVertex3f(j + 1.0f, i, 0.0f);
				glVertex3f(j + 1.0f, i + 1.0f, 0.0f);
				glVertex3f(j, i + 1.0f, 0.0f);
				glEnd();
				glFlush();
				break;
			}
			case MOVEWALL:
			{
				glColor3f(0.0f, 1.0f, 1.0f);
				glBegin(GL_POLYGON);
				glVertex3f(j, i, 0.0f);
				glVertex3f(j + 1.0f, i, 0.0f);
				glVertex3f(j + 1.0f, i + 1.0f, 0.0f);
				glVertex3f(j, i + 1.0f, 0.0f);
				glEnd();
				glFlush();
				break;
			}
			case SPAWN:
			{
				glColor3f(0.0f, 0.8f, 0.0f);
				glBegin(GL_POLYGON);
				glVertex3f(j, i, 0.0f);
				glVertex3f(j + 1.0f, i, 0.0f);
				glVertex3f(j + 1.0f, i + 1.0f, 0.0f);
				glVertex3f(j, i + 1.0f, 0.0f);
				glEnd();
				glFlush();
				break;
			}
			default:
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				glBegin(GL_POLYGON);
				glVertex3f(j, i, 0.0f);
				glVertex3f(j + 1.0f, i, 0.0f);
				glVertex3f(j + 1.0f, i + 1.0f, 0.0f);
				glVertex3f(j, i + 1.0f, 0.0f);
				glEnd();
				glFlush();
				break;
			}
			}
		}
	}
}

void WorldEngine::updateSquare(Point p, int type) {
	currentsectionx = p.x / ((glutGet(GLUT_WINDOW_WIDTH) - 166) / w);
	currentsectiony = (glutGet(GLUT_WINDOW_HEIGHT) - p.y) / (glutGet(GLUT_WINDOW_HEIGHT) / h);
	squares[currentsectiony * h + currentsectionx].type = type;
}
