#ifndef GLUIMANAGER_H
#define GLUIMANAGER_H

#include "openGL.h"
#include "InputManager.h"
#include "WorldEngine.h"

class GLUIManager {
public:
	enum FileManagement{SAVE, LOAD, NEW};
	static void reshape(int x, int y);
	static void menuEvents(int choice);
	static void initGLUI(int main_window, void updateGame());
	static WorldEngine engine;
	static GLUI_RadioGroup *radiogroup;

private:
	static GLUI *glui;
	static GLUI_EditText *filename;
	static GLUI_EditText *enterWidth;
	static GLUI_EditText *enterHeight;
	static GLUI_Panel *panel4;

	static void KeyHandling(unsigned char, int, int);
};

#endif
