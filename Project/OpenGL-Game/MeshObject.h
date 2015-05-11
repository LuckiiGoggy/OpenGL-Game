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
#include "Transform.h"

#include "openGL.h"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"
#include "LocationRect.h"
#include "BoundingBox.h"


#pragma once
class MeshObject: public Transform, public IGameObject, public IRenderable
{
public:
	MeshObject();
	~MeshObject();

	virtual void Update(float timeDelta);

	virtual bool Init(char* model_filename, char* vshader_filename, char* fshader_filename);

	void Render(void);
	virtual void RenderBoundingBox(void);
	
	void returnBB(glm::vec3, glm::vec3);

	void updateBoundingBox();
	void calculateBottomFace();

	GLuint program;

	BoundingBox boundingBox;
	LocationRect bottomFace;

private:
	virtual void SetUpCamera(void);
	virtual void BindBuffers(void);
	virtual void ReadObjFile(std::string filename);


	std::vector<glm::vec4> vertices;
	std::vector<glm::vec3> normals;
	std::vector<GLushort> elements;

	

	GLint attribute_v_coord;
	GLint attribute_v_normal;
	GLint uniform_m, uniform_v, uniform_p;
	GLint uniform_m_3x3_inv_transp, uniform_v_inv;

	GLuint vbo_vertices, vbo_normals, ibo_elements;
};

#endif