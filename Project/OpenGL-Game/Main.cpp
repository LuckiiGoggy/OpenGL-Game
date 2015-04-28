#include <iostream>
#include "openGL.h"
#include <gl/GLU.h>

#include "WorldEngine.h"
#include "InputManager.h"
#include "IGameObject.h"
#include "GroupObject.h"
#include "TestObject.h"
#include "MeshObject.h"

const int SAVE = 1;
const int LOAD = 2;
const int NEW = 3;
const int WIDTH = 400;
const int HEIGHT = 400;
const int GLUI_WIDTH = 166;	//not actually set-able by GLUI
int main_window;
int sub_window;
WorldEngine engine = WorldEngine(WIDTH, HEIGHT);
GLUI *glui;
GLUI_EditText *filename;
GLUI_EditText *enterWidth;
GLUI_EditText *enterHeight;
GLUI_RadioGroup *radiogroup;
GLUI_Panel *panel4;
void updateGame();
void menuEvents(int choice);
void renderScene(void);
MeshObject myMesh;

void reshape(int x, int y);
void initGLUI();

GroupObject test;

int main(int argc, char **argv) {
	int menu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);//optional
	glutInitWindowSize(WIDTH + GLUI_WIDTH, HEIGHT); //optional

	main_window = glutCreateWindow("COMP4900 Project");
	//sub_window = glutCreateSubWindow(main_window, 0, 0, WIDTH, HEIGHT);

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return 1;
	}
	if (glewIsSupported("GL_VERSION_4_0")) {
		std::cout << "GLEW Version is 4.0\n";
	}
	else {
		std::cout << "GLEW 4.0 not supported\n";
	}

	char* obj_filename = (char*) "../Assets/Models/suzanne.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	myMesh.Init(obj_filename, v_shader_filename, f_shader_filename);

	glutDisplayFunc(renderScene);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glDepthRange(1, 0);

	glutKeyboardFunc(InputManager::KeyPress);
	glutKeyboardUpFunc(InputManager::KeyUp);
	glutSpecialFunc(InputManager::SpecialKeyPress);
	glutSpecialUpFunc(InputManager::SpecialKeyUp);

	glutMouseFunc(InputManager::MouseInput);
	InputManager::Init();

	glutDisplayFunc(renderScene);
	
	//glutKeyboardFunc(InputManager::KeyPress);
	glutKeyboardUpFunc(InputManager::KeyUp);
	glutSpecialFunc(InputManager::SpecialKeyPress);
	glutSpecialUpFunc(InputManager::SpecialKeyUp);

	//glutMouseFunc(InputManager::MouseInput);

	glutMotionFunc(InputManager::MouseMotion);
	glutPassiveMotionFunc(InputManager::MouseMotion);

	glutReshapeFunc(reshape);

	//glutIdleFunc(updateGame);

	glutFullScreen();
	initGLUI();

	GLUI_Master.set_glutKeyboardFunc(InputManager::KeyPress);
	GLUI_Master.set_glutMouseFunc(InputManager::MouseInput);

	glutMainLoop();

	return 0;
}

void updateGame() {
	if (glutGetWindow() != main_window) glutSetWindow(main_window);

	if (InputManager::isKeyDown(KeyCodes::ESC)) glutLeaveMainLoop();

	if (InputManager::isLeftButtonDown() && engine.loaded == true) {
		Point p = InputManager::GetMousePos();
		engine.updateSquare(p, radiogroup->get_int_val());
	}
	
	if (InputManager::isKeyDown(KeyCodes::w)) myMesh.Move(glm::vec3(0.0f, 0.0f, 0.01f));
	if (InputManager::isKeyDown(KeyCodes::a)) myMesh.Move(glm::vec3(-0.01f, 0.0f, 0.0f));
	if (InputManager::isKeyDown(KeyCodes::s)) myMesh.Move(glm::vec3(0.0f, 0.0f, -0.01f));
	if (InputManager::isKeyDown(KeyCodes::d)) myMesh.Move(glm::vec3(0.01f, 0.0f, 0.0f));
	if (InputManager::isSpecialKeyDown(GLUT_KEY_SHIFT_L)) myMesh.Move(glm::vec3(0.0f, -0.01f, 0.0f));
	if (InputManager::isKeyDown(KeyCodes::Space)) myMesh.Move(glm::vec3(0.0f, 0.01f, 0.0f));



	glutPostRedisplay();
}

void menuEvents(int choice) {
	switch (choice) {
	case SAVE: {
		if (engine.loaded = true) {
			if (engine.writeWorld(filename->get_text())) {
				glui->add_statictext_to_panel(panel4, filename->get_text());
			}
		}
		break;
	}
	case LOAD: {
		engine.readWorld(filename->get_text());
		break;
	}
	case NEW: {
		if (engine.newWorld(filename->get_text(), enterWidth->get_text(), enterHeight->get_text())) {
			glui->add_statictext_to_panel(panel4, filename->get_text());
		}
		break;
	}
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1.0);

	myMesh.Update(0.0f);
	myMesh.Render();
	myMesh.RenderBoundingBox();

	if (engine.loaded == true) {
		engine.renderWorld();
	}


	glutSwapBuffers();
}

void reshape(int x, int y) {
	GLUI_Master.auto_set_viewport();

	glutPostRedisplay();
}

void initGLUI() {
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
}
