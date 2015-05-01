#include "Character.h"


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
	moveDelta.z += movementSpeed;
}
void Character::MoveBackward(void){
	moveDelta.z -= movementSpeed;
}

void Character::SetMovementSpeed(int speed){
	movementSpeed = speed;
}
int Character::GetMovementSpeed(void){
	return movementSpeed;
}

void Character::MoveMembers(){
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