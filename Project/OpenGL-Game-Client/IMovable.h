#ifndef IMOVABLE_H
#define IMOVABLE_H

#include "Dependencies\glm\glm\glm.hpp"


class IMovable{
protected:
	bool canMove;
public:
	IMovable();
	virtual void Move(glm::vec3) = 0;
#ifdef INDECISIVE
	virtual void MoveUp(int delta) = 0;
	virtual void MoveDown(int delta) = 0;
	virtual void MoveLeft(int delta) = 0;
	virtual void MoveRight(int delta) = 0;
	virtual void MoveForward(int delta) = 0;
	virtual void MoveBackward(int delta) = 0;
#endif
	virtual bool CanMove(){ return canMove; }
	virtual void SetMove(bool val){ canMove = val;  }
};

#endif