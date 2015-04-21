#include <iostream>
//#include "openGL.h"

//Santo Tallarico COMP4900 World Builder/Editor
#include "WorldEngine.h"

WorldEngine engine;
void renderScene(void);

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);//optional
	glutInitWindowSize(400, 400); //optional
	glutCreateWindow("OpenGL First Window");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_3")) {
		std::cout << " GLEW Version is 3.3\n ";
	}
	else {
		std::cout << "GLEW 3.3 not supported\n ";
	}

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(renderScene);

	glutMainLoop();

	return 0;
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	engine.readWorld();
	engine.writeWorld();

	glutSwapBuffers();
}
