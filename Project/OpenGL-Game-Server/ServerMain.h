#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#include "PhysicsEngine.h"
#include "IObject.h"
#include <string>
#include <map>

class ServerMain
{
public:
	static void Init(void);
	static PhysicsEngine *GetPhysEngi(void);
	static void SetPhysEngi(PhysicsEngine *);

	static void AddMember(std::string name, IObject *object);


protected:
	/*Members*/
	static std::map<std::string, IObject *> members;
	static PhysicsEngine *physEngi;
};

#endif