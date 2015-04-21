#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include <vector>
#include "Dependencies\glm\glm\glm.hpp";

#pragma once
class MeshObject
{
public:
	MeshObject();
	bool Load(	const char * path,
				std::vector<glm::vec3> & out_vertices,
				std::vector<glm::vec2> & out_uvs,
				std::vector<glm::vec3> & out_normals);
	~MeshObject();
};

#endif