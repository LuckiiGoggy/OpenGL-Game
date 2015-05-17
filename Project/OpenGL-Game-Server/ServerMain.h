#ifndef SERVERMAIN_H
#define SERVERMAIN_H


#include "ServerGame.h"
#include "PhysicsEngine.h"
#include "IObject.h"
#include <string>
#include <map>
#include "Transform.h"
#include "GameObjectContainer.h"
#include "Spawner.h"
#include "WorldEngine.h"

class ServerMain
{


public:
	enum MemberList { Players, Walls, Floors, Projectiles };
	static void Init(void);
	static PhysicsEngine *GetPhysEngi(void);
	static void SetPhysEngi(PhysicsEngine *);

	static void AddMember(MemberList listType, int objectId, IGameObject *object);
	static IGameObject *GetMember(MemberList listType, int objectId);

	static int GetNewObjectId(void);

	static void StartLoop();
	static void EndLoop();

	static void SendMemberPackets(GLNetwork::PacketType packet_t, GameObjectContainer members);

protected:
	/*Members*/
	static GameObjectContainer players;
	static GameObjectContainer walls;
	static GameObjectContainer floors;
	static GameObjectContainer projectiles;


	static PhysicsEngine *physEngi;
	static ServerGame *server;
	static bool isRunning;

	static float lastTime;
	static float currDelta;

	static int lastObjectId;

	static Spawner *spawner;
	static WorldEngine *engine;



};

#endif