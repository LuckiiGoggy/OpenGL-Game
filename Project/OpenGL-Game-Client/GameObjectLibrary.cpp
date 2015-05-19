#include "GameObjectLibrary.h"

MeshObject *GameObjectLibrary::spearObject;
MeshObject *GameObjectLibrary::wallObject;
MeshObject* GameObjectLibrary::floorObject;
MeshObject* GameObjectLibrary::idleObject;
MeshObject* GameObjectLibrary::walk1Object;
MeshObject* GameObjectLibrary::walk2Object;
WallObject *GameObjectLibrary::actualWallObject;



void GameObjectLibrary::InitGameObjects()
{
	char* spear_obj_filename = (char*) "../Assets/Models/spear.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.f.glsl";

	char* wall_filename = (char*) "../Assets/Models/wallCube.obj";
	char* v_wall_filename = (char*) "../Assets/Shaders/new-shading.v.glsl";
	char* f_wall_filename = (char*) "../Assets/Shaders/new-shading.f.glsl";

	char* floor_filename = (char*) "../Assets/Models/floorPlane.obj";
	char* v_floor_filename = (char*) "../Assets/Shaders/floor-shading.v.glsl";
	char* f_floor_filename = (char*) "../Assets/Shaders/floor-shading.f.glsl";

	char* obj_filename = (char*) "../Assets/Models/boxMan.obj";
	char* obj_filename1 = (char*) "../Assets/Models/boxManWalk1.obj";
	char* obj_filename2 = (char*) "../Assets/Models/boxManWalk2.obj";
	char* v_boxman_filename = (char*) "../Assets/Shaders/boxman-shading.v.glsl";
	char* f_boxman_filename = (char*) "../Assets/Shaders/boxman-shading.f.glsl";


	spearObject = new MeshObject();
	wallObject = new MeshObject();
	floorObject = new MeshObject();
	idleObject = new MeshObject();
	walk1Object = new MeshObject();
	walk2Object = new MeshObject();

	spearObject->Init(spear_obj_filename, v_shader_filename, f_shader_filename);
	wallObject->Init(wall_filename, v_wall_filename, f_wall_filename);
	floorObject->Init(floor_filename, v_floor_filename, f_floor_filename);
	idleObject->Init(obj_filename, v_boxman_filename, f_boxman_filename);
	walk1Object->Init(obj_filename1, v_boxman_filename, f_boxman_filename);
	walk2Object->Init(obj_filename2, v_boxman_filename, f_boxman_filename);
}

IGameObject * GameObjectLibrary::NewProjectile(void)
{
	return new MeshObject(*spearObject);
}

IGameObject * GameObjectLibrary::NewWall(void)
{
	return new MeshObject(*wallObject);
}

IGameObject * GameObjectLibrary::NewFloor(void)
{
	return new MeshObject(*floorObject);
}

IGameObject * GameObjectLibrary::NewPlayer(void)
{
	return new AnimatedObject(new MeshObject(*idleObject), new MeshObject(*walk1Object), new MeshObject(*walk2Object));
}

IGameObject * GameObjectLibrary::NewWallObject(void)
{
	return new WallObject(*wallObject);
}