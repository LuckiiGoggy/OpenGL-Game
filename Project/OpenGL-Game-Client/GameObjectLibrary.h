#ifndef GAMEOBJECTLIBRARY_H
#define GAMEOBJECTLIBRARY_H

#include "MeshObject.h"
#include "AnimatedObject.h"
#include "WallObject.h"

class GameObjectLibrary
{
public:
	static void InitGameObjects();

	static IGameObject *NewWall(void);
	static IGameObject *NewProjectile(void);
	static IGameObject *NewFloor(void);
	static IGameObject *NewPlayer(void);
	static IGameObject *NewWallObject(void);

protected:
	static MeshObject* spearObject;
	static MeshObject* wallObject;
	static MeshObject* floorObject;
	static MeshObject* idleObject;
	static MeshObject* walk1Object;
	static MeshObject* walk2Object;
	static WallObject* actualWallObject;
};

#endif