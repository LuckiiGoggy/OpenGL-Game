#ifndef IUPDATEABLE_H
#define IUPDATEABLE_H

class IUpdateable{
public:
	virtual void Update(float timeDelta) = 0;
};

#endif