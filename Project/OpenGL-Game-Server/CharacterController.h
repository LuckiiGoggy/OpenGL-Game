#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include <string>
#include <map>
#include <vector>
#include "Character.h"
#include "IUpdateable.h"
#include "InputManager.h"
#include "IGameObject.h"


class CharacterController: public IGameObject
{
public:
	CharacterController(Character *chara);
	~CharacterController();

	//virtual void AddControl(std::string, Character *);
	//virtual void RemoveControl(std::string);

	virtual void Update(float timeDelta);

protected:
	Character *chara;
	//Temporarily removing for simplification
	//std::map<std::string, Character *> controls; 
	std::map<KeyCodes, std::string> keyMapping;

	virtual std::vector<std::string> GetAllInputs();
	//virtual void ApplyAllInputs(std::vector<std::string>);
	virtual void ApplyAllInputs(std::vector<std::string> inputs);
};

#endif