#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <map>
#include "Dependencies\glm\glm\glm.hpp"

#include "GroupObject.h"
#include "IUpdateable.h"
#include "IRenderable.h"
#include "GameObjectContainer.h"
#include "CharacterStat.h"

/**Character Class is a container for the GroupObject that makes up
	a character.
	It provides the interface for interacting with a character.**/
class Character: public GroupObject, public GameObjectContainer
{
public:
	Character();
	~Character();
	virtual void Act(std::string funcName);
	
	virtual void MoveUp(void);
	virtual void MoveDown(void);
	virtual void MoveLeft(void);
	virtual void MoveRight(void);
	virtual void MoveForward(void);
	virtual void MoveBackward(void);

	virtual void RotateX(float angle);
	virtual void RotateY(float angle);
	virtual void RotateZ(float angle);

	virtual void SetMovementSpeed(int speed);
	virtual int  GetMovementSpeed();

	virtual void AddStat(CharacterStat newStat);
	virtual void RemoveStat(std::string statName);
	virtual int  GetStatValue(std::string statName);
	virtual void IncStat(std::string statName);
	virtual void DecStat(std::string statName);
	virtual void ResetStats(void);

	virtual void Update(float timeDelta);

	virtual IGameObject *GetBody(void);
	virtual void SetBody(IGameObject *);

protected:
	/**Collection of actions available to all characters.**/
	/**Note: when extending Character create a new collection and modify
		the Act function to read through your collection as well**/
	std::map<std::string, void(Character::*)(void)> baseActions;
	
	std::map<std::string, CharacterStat> charaStats;

	int movementSpeed;
	glm::vec3 moveDelta;

	IGameObject *body;
	
};

#endif