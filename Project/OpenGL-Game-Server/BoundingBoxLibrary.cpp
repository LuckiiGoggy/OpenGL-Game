#include "BoundingBoxLibrary.h"
#include "MeshObject.h"


BoundingBox *BoundingBoxLibrary::spearBox;
BoundingBox *BoundingBoxLibrary::wallBox;
BoundingBox *BoundingBoxLibrary::playerBox;

void BoundingBoxLibrary::InitBoxes()
{
	char* spear_obj_filename = (char*) "../Assets/Models/spear.obj";
	char* bottomFace_obj_filename = (char*) "../Assets/Models/face.obj";
	char* wallCube_obj_filename = (char*) "../Assets/Models/wallCube.obj";
	char* floorCube_obj_filename = (char*) "../Assets/Models/floorCube.obj";
	char* boxMan_obj_filename = (char*) "../Assets/Models/boxMan.obj";
	//char* sonic_obj_filename = (char*) "../Assets/Models/sonic.obj";
	char* v_shader_filename1 = (char*) "../Assets/Shaders/phong-shading.v.glsl";
	char* f_shader_filename1 = (char*) "../Assets/Shaders/phong-shading.f.glsl";

	MeshObject *spearMesh = new MeshObject();
	MeshObject *boxManMesh = new MeshObject();
	MeshObject *wallCubeMesh = new MeshObject();


	spearMesh->Init(spear_obj_filename, v_shader_filename1, f_shader_filename1);
	boxManMesh->Init(boxMan_obj_filename, v_shader_filename1, f_shader_filename1);
	wallCubeMesh->Init(wallCube_obj_filename, v_shader_filename1, f_shader_filename1);

	spearBox  = new BoundingBox(spearMesh->boundingBox);
  	playerBox = new BoundingBox(boxManMesh->boundingBox);
	wallBox   = new BoundingBox(wallCubeMesh->boundingBox);

	delete spearMesh;
	delete boxManMesh;
	delete wallCubeMesh;

	playerBox = NewPlayer();
	playerBox = NewPlayer();
	playerBox = NewPlayer();
	
}

BoundingBox * BoundingBoxLibrary::NewProjectile(void)
{
	return new BoundingBox(*spearBox);
}

BoundingBox * BoundingBoxLibrary::NewWall(void)
{
	return new BoundingBox(*wallBox);
}

BoundingBox * BoundingBoxLibrary::NewPlayer(void)
{
	return new BoundingBox(*playerBox);
}
