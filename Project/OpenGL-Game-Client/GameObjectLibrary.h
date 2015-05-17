#ifndef GAMEOBJECTLIBRARY_H
#define GAMEOBJECTLIBRARY_H

#include "MeshObject.h"

class GameObjectLibrary
{
public:
	static void InitGameObjects();

	static IGameObject *NewWall(void);
	static IGameObject *NewProjectile(void);
	static IGameObject *NewFloor(void);

protected:
	static MeshObject* spearObject;
	static MeshObject* wallObject;
	static MeshObject* floorObject;

};

#endif