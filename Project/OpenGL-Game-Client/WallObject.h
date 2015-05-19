#pragma once
#include "MeshObject.h"
class WallObject :
	public MeshObject
{
public:
	WallObject();
	WallObject(MeshObject &mesh) :MeshObject(mesh){};
	~WallObject();

	void Render(void);
};

