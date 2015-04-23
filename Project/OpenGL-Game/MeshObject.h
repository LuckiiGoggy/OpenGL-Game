#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "openGL.h"
#include "Renderable.h"

#pragma once
class MeshObject
{
public:
	MeshObject();
	bool Load(const char* filename);
	void Render();
	~MeshObject();

	std::vector<glm::vec4> getVerticies() { return vertices; }
	std::vector<glm::vec3> getNormals() { return normals; }
	std::vector<GLushort> getElements() { return elements; }

private:
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> elements;
};

#endif