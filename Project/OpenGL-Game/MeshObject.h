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
private:
	GLuint vbo_vertices, vbo_normals, ibo_elements;
public:
	MeshObject();
	~MeshObject();

	void load_obj(std::string filename);
	void Update(float timeDelta);
	int Init(char* model_filename, char* vshader_filename, char* fshader_filename, GLuint program);

	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> elements;
	glm::mat4 object2world;


	GLint attribute_v_coord = -1;
	GLint attribute_v_normal = -1;
	GLint uniform_m = -1, uniform_v = -1, uniform_p = -1;
	GLint uniform_m_3x3_inv_transp = -1, uniform_v_inv = -1;

	void upload(void);
	void draw(void);
	void draw_bbox(void);

	bool Init(char* model_filename, char* vshader_filename, char* fshader_filename);

	GLuint program;

};

#endif