#pragma once

class IMovable{
protected:
	bool canMove;
public:
	IMovable();
	virtual void Move(int x, int y, int z) = 0;
	virtual void MoveUp(int delta) = 0;
	virtual void MoveDown(int delta) = 0;
	virtual void MoveLeft(int delta) = 0;
	virtual void MoveRight(int delta) = 0;
	virtual void MoveForward(int delta) = 0;
	virtual void MoveBackward(int delta) = 0;
	virtual bool CanMove(){ return canMove; }
	virtual void SetMove(bool val){ canMove = val;  }
};