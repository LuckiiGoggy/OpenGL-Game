#include "CharacterController.h"
#include <iostream>

CharacterController::CharacterController(Character *chara)
{
	control = chara;
	/**Default KeyMapping**/
	keyMapping[KeyCodes::w] = "MoveForward";
	keyMapping[KeyCodes::s] = "MoveBackward";
	keyMapping[KeyCodes::a] = "MoveLeft";
	keyMapping[KeyCodes::d] = "MoveRight";
	keyMapping[KeyCodes::q] = "MoveUp";
	keyMapping[KeyCodes::e] = "MoveDown";
}


CharacterController::~CharacterController()
{
	if (control) delete control;
	/*
	std::map<std::string, Character *>::iterator iter;

	for (iter = controls.begin(); iter != controls.end(); ++iter) {
		delete iter->second;
	}
	controls.empty();
	*/
	keyMapping.empty();
}

/*
void CharacterController::AddControl(std::string name, Character * chara){
	controls[name] = chara;
}

void CharacterController::RemoveControl(std::string name){
	delete controls[name];
	controls.erase(name);
}
*/

void CharacterController::Update(float timeDelta){
	std::vector<std::string> inputs = GetAllInputs();
	ApplyAllInputs(inputs);

}


std::vector<std::string> CharacterController::GetAllInputs(){
	std::map<KeyCodes, std::string>::iterator keyMapIter;
	std::vector<std::string> inputs;
	for (keyMapIter = keyMapping.begin(); keyMapIter != keyMapping.end(); ++keyMapIter) {
		if (InputManager::isKeyDown(keyMapIter->first)){
			inputs.push_back(keyMapIter->second);
		}
	}

	return inputs;
}

/*
void CharacterController::ApplyAllInputs(std::vector<std::string> inputs){
	std::map<std::string, Character *>::iterator controlsIter;
	
	for (controlsIter = controls.begin(); controlsIter != controls.end(); ++controlsIter) {
		for (int i = 0; i < inputs.size(); i++){
			(controlsIter->second)->Act(inputs[i]);
		}
	}
}
*/
void CharacterController::ApplyAllInputs(std::vector<std::string> inputs){
	for (unsigned int i = 0; i < inputs.size(); i++){
		control->Act(inputs[i]);
	}
}