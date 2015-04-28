#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "openGL.h"
#include "IRenderable.h"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"

#pragma once
class MeshObject
{
public:
	MeshObject();
	~MeshObject();

	void Update(float timeDelta);

	void Render(void);
	void RenderBoundingBox(void);
	
	void Move(glm::vec3);
	void Rotate(glm::vec3, float);
	void Scale(glm::vec3);


	bool Init(char* model_filename, char* vshader_filename, char* fshader_filename);

	GLuint program;


private:
	void BindBuffers(void);
	void ReadObjFile(std::string filename);


	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> elements;
	glm::mat4 object2world;
	glm::mat4 world2camera;

	glm::mat4 sumRotation;
	glm::mat4 sumTranslation;
	glm::mat4 sumScale;


	GLint attribute_v_coord = -1;
	GLint attribute_v_normal = -1;
	GLint uniform_m = -1, uniform_v = -1, uniform_p = -1;
	GLint uniform_m_3x3_inv_transp = -1, uniform_v_inv = -1;

	GLuint vbo_vertices, vbo_normals, ibo_elements;
};

#endif