#include "AnimatedObject.h"
#include "MeshObject.h"


AnimatedObject::AnimatedObject()
{
	MeshObject *mesh1 = new MeshObject();
	MeshObject *mesh2 = new MeshObject();
	MeshObject *mesh3 = new MeshObject();

	char* obj_filename = (char*) "../Assets/Models/boxMan.obj";
	char* obj_filename1 = (char*) "../Assets/Models/boxManWalk1.obj";
	char* obj_filename2 = (char*) "../Assets/Models/boxManWalk2.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	mesh1->Init(obj_filename, v_shader_filename, f_shader_filename);
	mesh2->Init(obj_filename1, v_shader_filename, f_shader_filename);
	mesh3->Init(obj_filename2, v_shader_filename, f_shader_filename);

	AddMember("Idle", mesh1);
	AddMember("Walk1", mesh2);
	AddMember("Walk2", mesh3);

	frameNames.push_back("Idle");
	frameNames.push_back("Walk1");
	frameNames.push_back("Walk2");

	currentFrame = 0;
	timeBetweenFrames = 0.09f;
	timeSinceLastFrame = 0.0f;
}


AnimatedObject::~AnimatedObject()
{
}

void AnimatedObject::Update(float timeDelta){
	UpdateMembers(timeDelta);

	timeSinceLastFrame += timeDelta;
	if (timeSinceLastFrame >= timeBetweenFrames){
		timeSinceLastFrame = 0.0f;
		if (++currentFrame >= frameNames.size()){
			currentFrame = 0;
		}
	}

}
void AnimatedObject::Render(void){
	IRenderable *currMesh = dynamic_cast<IRenderable *>(GetMember(frameNames[currentFrame]));

	if (currMesh != 0) currMesh->Render();
}

void AnimatedObject::Move(float dX, float dY, float dZ, Space transformSpace){
	MoveMembers(dX, dY, dZ);
}

void AnimatedObject::Move(glm::vec3 moveDelta, Space transformSpace){
	MoveMembers(moveDelta);
}

void AnimatedObject::Rotate(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint, Space transformSpace){
	RotateMembers(axisX, axisY, axisZ, angle, rotPoint, transformSpace);
}
