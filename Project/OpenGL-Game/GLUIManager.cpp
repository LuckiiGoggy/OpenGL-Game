#include "GLUIManager.h"

const int SAVE = 1;
const int LOAD = 2;
const int NEW = 3;

void GLUIManager::reshape(int x, int y) {
	GLUI_Master.auto_set_viewport();

	glutPostRedisplay();
}

void GLUIManager::menuEvents(int choice) {
	switch (choice) {
	case FileManagement::SAVE: {
		if (engine.loaded = true) {
			if (engine.writeWorld(filename->get_text())) {
				glui->add_statictext_to_panel(panel4, filename->get_text());
			}
		}
		break;
	}
	case FileManagement::LOAD: {
		engine.readWorld(filename->get_text());
		break;
	}
	case FileManagement::NEW: {
		if (engine.newWorld(filename->get_text(), enterWidth->get_text(), enterHeight->get_text())) {
			glui->add_statictext_to_panel(panel4, filename->get_text());
		}
		break;
	}
	}
}

void GLUIManager::initGLUI(int main_window, void updateGame()) {
	engine = WorldEngine();
	glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);
	glui->set_main_gfx_window(main_window);

	GLUI_Panel *panel = glui->add_panel("File Management", GLUI_PANEL_EMBOSSED);
	filename = glui->add_edittext_to_panel(panel, "Filename: ", GLUI_EDITTEXT_TEXT);
	GLUI_Button *saveButton = glui->add_button_to_panel(panel, "Save", SAVE, menuEvents);
	GLUI_Button *loadButton = glui->add_button_to_panel(panel, "Load", LOAD, menuEvents);
	GLUI_Button *newButton = glui->add_button_to_panel(panel, "New", NEW, menuEvents);

	GLUI_Panel *panel2 = glui->add_panel("Geometry Select", GLUI_PANEL_EMBOSSED);
	radiogroup = glui->add_radiogroup_to_panel(panel2);
	GLUI_RadioButton *wall = glui->add_radiobutton_to_group(radiogroup, "Wall");
	GLUI_RadioButton *floor = glui->add_radiobutton_to_group(radiogroup, "Floor");
	GLUI_RadioButton *movewall = glui->add_radiobutton_to_group(radiogroup, "Moveable Wall");
	GLUI_RadioButton *spawn = glui->add_radiobutton_to_group(radiogroup, "Spawn Point");

	GLUI_Panel *panel3 = glui->add_panel("World Properties", GLUI_PANEL_EMBOSSED);
	enterWidth = glui->add_edittext_to_panel(panel3, "Width: ", GLUI_EDITTEXT_TEXT);
	enterHeight = glui->add_edittext_to_panel(panel3, "Height: ", GLUI_EDITTEXT_TEXT);

	engine.loadDirectory();
	panel4 = glui->add_panel("Level Files", GLUI_PANEL_EMBOSSED);
	for (int i = 0; i < engine.levelNames.size(); i++) {
		glui->add_statictext_to_panel(panel4, engine.levelNames[i].c_str());
	}

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc(updateGame);
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutKeyboardFunc(InputManager::KeyPress);
	GLUI_Master.set_glutMouseFunc(InputManager::MouseInput);
}
