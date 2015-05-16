#ifndef SERVERMAIN_H
#define SERVERMAIN_H


#include "ServerGame.h"
#include "PhysicsEngine.h"
#include "IObject.h"
#include <string>
#include <map>
#include "Transform.h"

class ServerMain
{
public:
	static void Init(void);
	static PhysicsEngine *GetPhysEngi(void);
	static void SetPhysEngi(PhysicsEngine *);

	static void AddMember(int objectId, Transform *object);
	static Transform *GetMember(int objectId);

	static int GetNewObjectId(void);

	static void StartLoop();
	static void EndLoop();

protected:
	/*Members*/
	static std::map<int, Transform*> members;
	static PhysicsEngine *physEngi;
	static ServerGame *server;
	static bool isRunning;

	static float lastTime;
	static float currDelta;

	static int lastObjectId;



};

#endif