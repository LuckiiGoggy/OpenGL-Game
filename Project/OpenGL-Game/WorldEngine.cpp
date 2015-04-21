//Santo Tallarico COMP4900 World Builder/Editor
#include "WorldEngine.h"

WorldEngine::WorldEngine() {

}

void WorldEngine::readWorld() {
	std::ifstream file;
	file.open("level.dat");

	if (file.is_open()) {
		int index;
		int block;
		std::string s;

		std::getline(file, s);
		w = (float)(s.at(0) - '0');
		std::getline(file, s);
		h = (float)(s.at(0) - '0');

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
				}
			}
		}

		file.close();
	}
}

void WorldEngine::writeWorld() {
	std::ofstream file;
	file.open("level2.dat");

	if (file.is_open()) {
		file << w << std::endl;
		file << h << std::endl;
		for (std::vector<int>::size_type i = 0; i != squares.size(); i++) {
			file << squares.at(i).type;
			if (i % 8 == 0 && i != 0) {
				file << std::endl;
			}
		}

		file.close();
	}
}
