#include "Player.h"
#include "GroupObject.h"
#include "Camera.h"
#include "MeshObject.h"
#include "GlutManager.h"

Player::Player(void)
{
	GroupObject *group = new GroupObject();
	Camera *camera = new Camera();
	MeshObject *mesh = new MeshObject();
	MeshObject *mesh2 = new MeshObject();
	chara = new Character();
	controller = new CharacterController(chara);
	
	char* obj_filename = (char*) "../Assets/Models/floorCube.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	mesh->Init(obj_filename, v_shader_filename, f_shader_filename);
	mesh2->Init(obj_filename, v_shader_filename, f_shader_filename);

	//camera->Move(glm::vec3(0.0f, 3.0f, 4.0f));
	//camera->SetCameraLookAt(glm::vec3(-0.0f, -2.0f, 8.0f));
	mesh2->Move(1.0f, 2.0f, 0.0f);

	group->AddMember("Mesh", mesh);
	//group->AddMember("Mesh2", mesh2);
	group->AddMember("Camera", camera);

	

	chara->AddMember("Sonic", group);

	GlutManager::SetMainCamera(camera);
}


Player::~Player(void)
{
	if(chara)		delete chara;
	if(controller)  delete controller;
}

void Player::Update(float timeDelta){
	
	if (InputManager::isSpecialKeyDown(GLUT_KEY_LEFT))	chara->RotateY(1.0f  * timeDelta);
	if (InputManager::isSpecialKeyDown(GLUT_KEY_RIGHT)) chara->RotateY(-1.0f * timeDelta);
	if (InputManager::isSpecialKeyDown(GLUT_KEY_UP))	chara->RotateX(1.0f  * timeDelta);
	if (InputManager::isSpecialKeyDown(GLUT_KEY_DOWN))	chara->RotateX(-1.0f * timeDelta);
	if (InputManager::isKeyDown(','))					chara->RotateZ(0.1f  * timeDelta);
	if (InputManager::isKeyDown('.'))					chara->RotateZ(-0.1f * timeDelta);


	controller->Update(timeDelta);
	chara->Update(timeDelta);
}

void Player::Render(void){
	chara->Render();
}