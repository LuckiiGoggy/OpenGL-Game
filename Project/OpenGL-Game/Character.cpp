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
}

void Character::Update(float timeDelta){
	MoveMembers(moveDelta * timeDelta);
	UpdateMembers(timeDelta);
	position += moveDelta *  timeDelta;

	moveDelta = glm::vec3(0.0f);
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

void Character::Act(std::string funcName){
	std::map<std::string, void(Character::*)(void)>::iterator it = baseActions.find(funcName);
	if (it != baseActions.end()) (this->*(it->second))();
}

void Character::Render(void){
	RenderMembers();
}

void Character::RotateX(float angle){
	RotateMembers(1.0f, 0.0f, 0.0f, angle);
}
void Character::RotateY(float angle){
	RotateMembers(0.0f, 1.0f, 0.0f, angle);
}
void Character::RotateZ(float angle){
	RotateMembers(0.0f, 0.0f, 1.0f, angle);
}


void Character::AddStat(CharacterStat newStat){
	charaStats[newStat.GetName()] = newStat;
}
void Character::RemoveStat(std::string statName){
	charaStats.erase(statName);

}
int  Character::GetStatValue(std::string statName){
	std::map<std::string, CharacterStat>::iterator it = charaStats.find(statName);
	if (it != charaStats.end()) return (it->second).GetValue();

	return -1;
}
void Character::IncStat(std::string statName){
	std::map<std::string, CharacterStat>::iterator it = charaStats.find(statName);
	if (it != charaStats.end()) (it->second)+= 1;
}
void Character::DecStat(std::string statName){
	std::map<std::string, CharacterStat>::iterator it = charaStats.find(statName);
	if (it != charaStats.end()) (it->second)-= 1;
}
void Character::ResetStats(void){
	std::map<std::string, CharacterStat>::iterator it;

	for (it = charaStats.begin(); it != charaStats.end(); ++it){
		(it->second).Reset();
	}
}