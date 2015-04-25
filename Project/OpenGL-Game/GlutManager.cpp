#include "openGL.h"
#include <iostream>
#include "GlutManager.h"
#include "IRenderable.h"

std::map<AllowedMembers, std::map<std::string, IObject *>> GlutManager::members;


GlutManager::GlutManager()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 200);//optional
	glutInitWindowSize(400, 400); //optional

	glutCreateWindow("OpenGL First Window");

	glewInit();
	if (glewIsSupported("GL_VERSION_4_0")) {
		std::cout << "GLEW Version is 4.0\n";
	}
	else {
		std::cout << "GLEW 4.0 not supported\n";
	}

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(GlutManager::RenderScene);
	glutIdleFunc(GlutManager::IdleFunc);

}


GlutManager::~GlutManager()
{
}

void GlutManager::StartLoop(void){
	glutMainLoop();
}

void GlutManager::EndLoop(void){
	/**Clean Up**/
	glutLeaveMainLoop();
}

void GlutManager::RenderScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	std::map<std::string, IObject *>::iterator iter;
	
	for (iter = members[Renderable].begin(); iter != members[Renderable].end(); ++iter) {
		if (((IRenderable *)iter->second)->IsVisible()) ((IRenderable *)iter->second)->Render();
	}

	glutSwapBuffers();
}

void GlutManager::IdleFunc(void){

}

