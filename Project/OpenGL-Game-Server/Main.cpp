#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

#include "ServerMain.h"


int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	//glutInitWindowPosition(200, 200);//optional
	//glutInitWindowSize(566, 400); //optional

	GLint mainWindow = glutCreateWindow("OpenGL First Window");
	glewInit();
	ServerMain::Init();

	glutHideWindow();
// 	GlutManager::Init(false);
// 	InputManager::Init();	
// 
// 
// 	GameScene *gS = new GameScene();
// 	gS->Init();
// 	GlutManager::AddMember("Derp", gS);
// 
// 	GlutManager::StartLoop();

	
	ServerMain::StartLoop();

	return 0;
}
