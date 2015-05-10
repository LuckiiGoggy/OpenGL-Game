#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "IGameObject.h"
#include "IRenderable.h"
#include "IMovable.h"

#include "openGL.h"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"
#include "LocationRect.h"
#include "BoundingBox.h"


#pragma once
class MeshObject: public IGameObject, public IRenderable, public IMovable
{
public:
	MeshObject();
	~MeshObject();

	virtual void Update(float timeDelta);

	virtual bool Init(char* model_filename, char* vshader_filename, char* fshader_filename);

	void Render(void);
	virtual void RenderBoundingBox(void);
	
	virtual void Move(glm::vec3);
	virtual void Move(float x, float y, float z);
	virtual void MoveTo(float x, float y, float z);
	virtual void Rotate(glm::vec3, float);
	virtual void Scale(glm::vec3);
	virtual void Scale(float x, float y, float z);
	void returnBB(glm::vec3, glm::vec3);
	

	glm::mat4 sumTranslation;
	GLuint program;


private:
	virtual void SetUpCamera(void);
	virtual void BindBuffers(void);
	virtual void ReadObjFile(std::string filename);


	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> elements;
	glm::mat4 object2world;

	glm::mat4 sumRotation;
	glm::mat4 sumScale;

	BoundingBox boundingBox;
	LocationRect bottomFace;

	GLint attribute_v_coord;
	GLint attribute_v_normal;
	GLint uniform_m, uniform_v, uniform_p;
	GLint uniform_m_3x3_inv_transp, uniform_v_inv;

	GLuint vbo_vertices, vbo_normals, ibo_elements;
};

#endif