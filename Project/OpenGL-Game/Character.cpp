#include "Character.h"
#include "MeshObject.h"
#include "Camera.h"


Character::Character()
{
	movementSpeed = 1;
	moveDelta = glm::vec3(0.0);
	position = glm::vec3(0.0);

	baseActions["MoveUp"]		= &Character::MoveUp;
	baseActions["MoveDown"]		= &Character::MoveDown;
	baseActions["MoveLeft"]		= &Character::MoveLeft;
	baseActions["MoveRight"]	= &Character::MoveRight;
	baseActions["MoveForward"]	= &Character::MoveForward;
	baseActions["MoveBackward"] = &Character::MoveBackward;
}


Character::~Character()
{
	std::map<std::string, GroupObject *>::iterator iter;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		#ifdef DEBUG
		std::cout << "\n\tDeleting " << iter->first;
		#endif
		delete iter->second;
	}
	members.empty();
}

void Character::Update(float timeDelta){
	moveDelta *= timeDelta;

	std::map<std::string, GroupObject *>::iterator iter;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		(iter->second)->Update(timeDelta);
	}

	position += moveDelta;
	MoveMembers();
}

void Character::MoveUp(void){
	moveDelta.y += movementSpeed;
}
void Character::MoveDown(void){
	moveDelta.y -= movementSpeed;
}
void Character::MoveLeft(void){
	moveDelta.x -= movementSpeed;
}
void Character::MoveRight(void){
	moveDelta.x += movementSpeed;
}
void Character::MoveForward(void){
	moveDelta.z -= movementSpeed;
}
void Character::MoveBackward(void){
	moveDelta.z += movementSpeed;
}

void Character::SetMovementSpeed(int speed){
	movementSpeed = speed;
}
int Character::GetMovementSpeed(void){
	return movementSpeed;
}

void Character::MoveMembers(){
	if (moveDelta == glm::vec3(0.0f)) return;

	std::map<std::string, GroupObject *>::iterator iter;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		(iter->second)->Move(moveDelta);
	}
}

void Character::Act(std::string funcName){
	std::map<std::string, void(Character::*)(void)>::iterator it = baseActions.find(funcName);
	if (it != baseActions.end()) (this->*(it->second))();
}

void Character::AddMember(std::string name, GroupObject * obj){
	members[name] = obj;
}

void Character::RemoveMember(std::string name){
	delete members[name];

	members.erase(name);
}

void Character::Render(void){
	std::map<std::string, GroupObject *>::iterator iter;

	for (iter = members.begin(); iter != members.end(); ++iter) {
		(iter->second)->Render();
	}
}

void Character::RotateX(float angle){
	MeshObject *mesh = dynamic_cast<MeshObject *>((members["Sonic"])->GetMember("Mesh"));
	Camera *camera = dynamic_cast<Camera *>((members["Sonic"])->GetMember("Camera"));

	//mesh->Rotate(glm::vec3(1.0f, 0.0f, 0.0f), angle);
	//camera->RotateAtLookAtX(angle);
}
void Character::RotateY(float angle){
	MeshObject *mesh = dynamic_cast<MeshObject *>((members["Sonic"])->GetMember("Mesh"));

	MeshObject *mesh2 = dynamic_cast<MeshObject *>((members["Sonic"])->GetMember("Mesh2"));
	Camera *camera = dynamic_cast<Camera *>((members["Sonic"])->GetMember("Camera"));

	mesh->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), angle);
	//mesh2->Rotate(glm::vec3(0.0f, 1.0f, 0.0f), angle);
	camera->RotateAtLookAtY(angle);
}
void Character::RotateZ(float angle){
	MeshObject *mesh = dynamic_cast<MeshObject *>((members["Sonic"])->GetMember("Mesh"));
	Camera *camera = dynamic_cast<Camera *>((members["Sonic"])->GetMember("Camera"));

	//mesh->Rotate(glm::vec3(0.0f, 0.0f, 1.0f), angle);
	//camera->RotateAtLookAtZ(angle);
}