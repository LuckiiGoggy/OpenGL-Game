//Santo Tallarico COMP4900 World Builder/Editor
#include "WorldEngine.h"

WorldEngine::WorldEngine() {
	loaded = false;
	filetype = ".lvl";
	path = "../Assets/Levels/";
}

void WorldEngine::readWorld() {
	DIR *dir;
	int numFiles = 0;
	struct dirent *ent;
	if ((dir = opendir("../Assets/Levels")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_namlen > filetype.size()) {
				//if (filetype.compare(ent->d_namlen - filetype.size() - 1, filetype.size(), ent->d_name) == 0) {
					numFiles++;
					std::cout << numFiles << ": "<< ent->d_name << std::endl;
					levelNames.push_back(ent->d_name);
				//}
			}
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
		return;
	}

	std::cout << "Enter file number to load: ";
	int fileNum;
	std::cin >> fileNum;

	std::ifstream file;
	if (fileNum > 0 && fileNum <= levelNames.size()) {
		file.open(path + levelNames[fileNum - 1]);
	}

	if (file.is_open()) {
		int index;
		int block;
		std::string s;

		std::getline(file, s);
		w = stof(s);
		std::getline(file, s);
		h = stof(s);

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

void WorldEngine::writeWorld() {
	std::ofstream file;
	file.open(path + "level2.lvl", std::ofstream::out | std::ofstream::trunc);

	if (file.is_open()) {
		file << w << std::endl;
		file << h << std::endl;
		for (std::vector<int>::size_type i = 0; i != squares.size(); i++) {
			if (i % 8 == 0 && i != 0) {
				file << std::endl;
			}
			file << squares.at(i).type;
		}

		file.close();
	}
}

void WorldEngine::renderWorld() {
	int index = 0;
	int block;
	for (float i = 0; i < h; i++) {
		for (float j = 0; j < w; j++) {
			block = squares.at(index).type;
			index++;
			switch (block) {
			case 1:
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
			case 2:
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
			case 3:
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
