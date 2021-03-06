#include "MeshObject.h"
#include <algorithm>
#include <iostream>
#include "shader_utils.h"
#include "GlutManager.h"

MeshObject::MeshObject() : vbo_vertices(0), vbo_normals(0), ibo_elements(0)
{
	attribute_v_coord = -1;
	attribute_v_normal = -1;
	uniform_m = -1;
	uniform_v = -1;
	uniform_p = -1;
	uniform_m_3x3_inv_transp = -1;
	uniform_v_inv = -1;
}

MeshObject::~MeshObject() {
	if (vbo_vertices != 0)
		glDeleteBuffers(1, &vbo_vertices);
	if (vbo_normals != 0)
		glDeleteBuffers(1, &vbo_normals);
	if (ibo_elements != 0)
		glDeleteBuffers(1, &ibo_elements);

	glDeleteProgram(program);
}


void MeshObject::ReadObjFile(std::string filename){
	std::ifstream in(filename, std::ios::in);
	if (!in) { std::cout << "Cannot open " << filename << std::endl; exit(1); }
	std::vector<int> nb_seen;

	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::istringstream s(line.substr(2));
			glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0;
			vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a; s >> b; s >> c;
			a--; b--; c--;
			elements.push_back(a); elements.push_back(b); elements.push_back(c);
		}
		else if (line[0] == '#') { /* ignoring this line */ }
		else { /* ignoring this line */ }
	}

	normals.resize(vertices.size(), glm::vec3(0.0, 0.0, 0.0));
	nb_seen.resize(vertices.size(), 0);
	for (unsigned int i = 0; i < elements.size(); i += 3) {
		GLushort ia = elements[i];
		GLushort ib = elements[i + 1];
		GLushort ic = elements[i + 2];
		glm::vec3 normal = glm::normalize(glm::cross(
			glm::vec3(vertices[ib]) - glm::vec3(vertices[ia]),
			glm::vec3(vertices[ic]) - glm::vec3(vertices[ia])));

		int v[3];  v[0] = ia;  v[1] = ib;  v[2] = ic;
		for (int j = 0; j < 3; j++) {
			GLushort cur_v = v[j];
			nb_seen[cur_v]++;
			if (nb_seen[cur_v] == 1) {
				normals[cur_v] = normal;
			}
			else {
				// average
				normals[cur_v].x = (float)normals[cur_v].x * (1.0 - 1.0 / nb_seen[cur_v]) + normal.x * 1.0 / nb_seen[cur_v];
				this->normals[cur_v].y = (float)this->normals[cur_v].y * (1.0 - 1.0 / nb_seen[cur_v]) + normal.y * 1.0 / nb_seen[cur_v];
				this->normals[cur_v].z = (float)this->normals[cur_v].z * (1.0 - 1.0 / nb_seen[cur_v]) + normal.z * 1.0 / nb_seen[cur_v];
				this->normals[cur_v] = glm::normalize(this->normals[cur_v]);
			}
		}
	}
}


/**
* Store object vertices, normals and/or elements in graphic card
* buffers
*/
void MeshObject::BindBuffers() {
	if (this->vertices.size() > 0) {
		glGenBuffers(1, &this->vbo_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(this->vertices[0]),
			this->vertices.data(), GL_STATIC_DRAW);
	}

	if (this->normals.size() > 0) {
		glGenBuffers(1, &this->vbo_normals);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_normals);
		glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(this->normals[0]),
			this->normals.data(), GL_STATIC_DRAW);
	}

	if (this->elements.size() > 0) {
		glGenBuffers(1, &this->ibo_elements);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo_elements);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof(this->elements[0]),
			this->elements.data(), GL_STATIC_DRAW);
	}
}

/**
* Draw the object
*/
void MeshObject::Render() {
	if (vbo_vertices != 0) {
		glEnableVertexAttribArray(attribute_v_coord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glVertexAttribPointer(
			attribute_v_coord,  // attribute
			4,                  // number of elements per vertex, here (x,y,z,w)
			GL_FLOAT,           // the type of each element
			GL_FALSE,           // take our values as-is
			0,                  // no extra data between each position
			0                   // offset of first element
			);
	}

	if (vbo_normals != 0) {
		glEnableVertexAttribArray(attribute_v_normal);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glVertexAttribPointer(
			attribute_v_normal, // attribute
			3,                  // number of elements per vertex, here (x,y,z)
			GL_FLOAT,           // the type of each element
			GL_FALSE,           // take our values as-is
			0,                  // no extra data between each position
			0                   // offset of first element
			);
	}


	/* Apply object's transformation matrix */
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(netTransformations));
	/* Transform normal vectors with transpose of inverse of upper left
	3x3 model matrix (ex-gl_NormalMatrix): */
	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(netTransformations)));
	glUniformMatrix3fv(uniform_m_3x3_inv_transp, 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));

	/* Push each element in buffer_vertices to the vertex shader */
	if (ibo_elements != 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
		int size;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}

	if (vbo_normals != 0)
		glDisableVertexAttribArray(attribute_v_normal);
	if (vbo_vertices != 0)
		glDisableVertexAttribArray(attribute_v_coord);

	RenderBoundingBox();
}

void MeshObject::SetUpCamera(){

}




/**
* Draw object bounding box
*/
void MeshObject::RenderBoundingBox() {

	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5, 0.5, -0.5, 1.0,
		-0.5, 0.5, -0.5, 1.0,
		-0.5, -0.5, 0.5, 1.0,
		0.5, -0.5, 0.5, 1.0,
		0.5, 0.5, 0.5, 1.0,
		-0.5, 0.5, 0.5, 1.0,
	};
	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5, 2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLfloat
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;
	min_x = max_x = this->vertices[0].x;
	min_y = max_y = this->vertices[0].y;
	min_z = max_z = this->vertices[0].z;
	for (unsigned int i = 0; i < this->vertices.size(); i++) {
		if (this->vertices[i].x < min_x) min_x = this->vertices[i].x;
		if (this->vertices[i].x > max_x) max_x = this->vertices[i].x;
		if (this->vertices[i].y < min_y) min_y = this->vertices[i].y;
		if (this->vertices[i].y > max_y) max_y = this->vertices[i].y;
		if (this->vertices[i].z < min_z) min_z = this->vertices[i].z;
		if (this->vertices[i].z > max_z) max_z = this->vertices[i].z;
	}

	returnBB(glm::vec3(min_x, min_y, min_z), glm::vec3(max_x, max_y, max_z));

	glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
	glm::vec3 center = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
	glm::mat4 transform = glm::scale(glm::mat4(1), size) * glm::translate(glm::mat4(1), center);

	/* Apply object's transformation matrix */
	glm::mat4 m = this->netTransformations * transform;
	glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(m));

	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(attribute_v_coord);
	glVertexAttribPointer(
		attribute_v_coord,  // attribute
		4,                  // number of elements per vertex, here (x,y,z,w)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4 * sizeof(GLushort)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8 * sizeof(GLushort)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(attribute_v_coord);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);
}
void MeshObject::calculateBottomFace()
{
	bottomFace = LocationRect(boundingBox.v1.x, boundingBox.v1.z, boundingBox.v8.x, boundingBox.v8.z);
	//bottomFace = LocationRect(v1_world.x, v1_world.z, v8_world.x, v8_world.z);
	//bottomFace = LocationRect(startPoint.x, startPoint.z, endPoint.x, endPoint.z);

	//v2
	//bottomFace = LocationRect(boundingBox.v1.x, boundingBox.v8.z, boundingBox.v8.x, boundingBox.v1.z);
	//bottomFace = LocationRect(v1_world.x, v8_world.z, v8_world.x, v1_world.z);
	//bottomFace = LocationRect(startPoint.x, endPoint.z, endPoint.x, startPoint.z);
}
void MeshObject::updateBoundingBox()
{
	//Apply world transformation to bounding box
	//*
	glm::vec4 v1_world = (this->netTransformations * glm::vec4(boundingBox.v1.x, boundingBox.v1.y, boundingBox.v1.z, 1));
	glm::vec4 v2_world = (this->netTransformations * glm::vec4(boundingBox.v2.x, boundingBox.v2.y, boundingBox.v2.z, 1));
	glm::vec4 v3_world = (this->netTransformations * glm::vec4(boundingBox.v3.x, boundingBox.v3.y, boundingBox.v3.z, 1));
	glm::vec4 v4_world = (this->netTransformations * glm::vec4(boundingBox.v4.x, boundingBox.v4.y, boundingBox.v4.z, 1));
	glm::vec4 v5_world = (this->netTransformations * glm::vec4(boundingBox.v5.x, boundingBox.v5.y, boundingBox.v5.z, 1));
	glm::vec4 v6_world = (this->netTransformations * glm::vec4(boundingBox.v6.x, boundingBox.v6.y, boundingBox.v6.z, 1));
	glm::vec4 v7_world = (this->netTransformations * glm::vec4(boundingBox.v7.x, boundingBox.v7.y, boundingBox.v7.z, 1));
	glm::vec4 v8_world = (this->netTransformations * glm::vec4(boundingBox.v8.x, boundingBox.v8.y, boundingBox.v8.z, 1));
	//*/

	//*
	boundingBox.v1 = glm::vec3(v1_world);
	boundingBox.v2 = glm::vec3(v2_world);
	boundingBox.v3 = glm::vec3(v3_world);
	boundingBox.v4 = glm::vec3(v4_world);
	boundingBox.v5 = glm::vec3(v5_world);
	boundingBox.v6 = glm::vec3(v6_world);
	boundingBox.v7 = glm::vec3(v7_world);
	boundingBox.v8 = glm::vec3(v8_world);//*/

	//Calculate the updated bottomFace of the bounding box
	calculateBottomFace();

	//Recalculate the directional radius of the bounding box
	boundingBox.refresh();
}
void MeshObject::returnBB(glm::vec3 startPoint, glm::vec3 endPoint)
{
	UpdateNetTransformations();
	//This function is called every time this object is rendered

	//start point is the closest vertex on the bottom left of a cube
	//the end point is the furthest vertex on the top right of the cube

	//Setup raw bounding box
	//*
	//startPoint = v2 Bottom Left Front
	//endPoint = v8 Top Right Back
	boundingBox = BoundingBox(true);
	boundingBox.v1 = glm::vec3(startPoint.x, endPoint.y, startPoint.z);
	boundingBox.v2 = glm::vec3(startPoint.x, startPoint.y, startPoint.z);
	boundingBox.v3 = glm::vec3(endPoint.x, startPoint.y, startPoint.z);
	boundingBox.v4 = glm::vec3(endPoint.x, endPoint.y, startPoint.z);
	boundingBox.v5 = glm::vec3(startPoint.x, endPoint.y, endPoint.z);
	boundingBox.v6 = glm::vec3(startPoint.x, startPoint.y, endPoint.z);
	boundingBox.v7 = glm::vec3(endPoint.x, startPoint.y, endPoint.z);
	boundingBox.v8 = glm::vec3(endPoint.x, endPoint.y, endPoint.z);//*/

	//Apply world transformation to bounding box
	//*
	glm::vec4 v1_world = (this->netTransformations * glm::vec4(boundingBox.v1.x, boundingBox.v1.y, boundingBox.v1.z, 1));
	glm::vec4 v2_world = (this->netTransformations * glm::vec4(boundingBox.v2.x, boundingBox.v2.y, boundingBox.v2.z, 1));
	glm::vec4 v3_world = (this->netTransformations * glm::vec4(boundingBox.v3.x, boundingBox.v3.y, boundingBox.v3.z, 1));
	glm::vec4 v4_world = (this->netTransformations * glm::vec4(boundingBox.v4.x, boundingBox.v4.y, boundingBox.v4.z, 1));
	glm::vec4 v5_world = (this->netTransformations * glm::vec4(boundingBox.v5.x, boundingBox.v5.y, boundingBox.v5.z, 1));
	glm::vec4 v6_world = (this->netTransformations * glm::vec4(boundingBox.v6.x, boundingBox.v6.y, boundingBox.v6.z, 1));
	glm::vec4 v7_world = (this->netTransformations * glm::vec4(boundingBox.v7.x, boundingBox.v7.y, boundingBox.v7.z, 1));
	glm::vec4 v8_world = (this->netTransformations * glm::vec4(boundingBox.v8.x, boundingBox.v8.y, boundingBox.v8.z, 1));
	//*/

	//*
	boundingBox.v1 = glm::vec3(v1_world);
	boundingBox.v2 = glm::vec3(v2_world);
	boundingBox.v3 = glm::vec3(v3_world);
	boundingBox.v4 = glm::vec3(v4_world);
	boundingBox.v5 = glm::vec3(v5_world);
	boundingBox.v6 = glm::vec3(v6_world);
	boundingBox.v7 = glm::vec3(v7_world);
	boundingBox.v8 = glm::vec3(v8_world);//*/


	//Recalculate the directional radius of the bounding box
	boundingBox.refresh();

	//Calculate the updated bottomFace of the bounding box
	calculateBottomFace();
}

void MeshObject::Update(float timeDelta){
	UpdateNetTransformations(); 
	UpdateBoundingBox(timeDelta);
	// Projection
	glm::mat4 camera2screen = glm::perspective(45.0f, 1.0f*glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);


	glUseProgram(program);
	glUniformMatrix4fv(uniform_v, 1, GL_FALSE, glm::value_ptr(GlutManager::GetMainCamera()->GetCameraMat()));
	glUniformMatrix4fv(uniform_p, 1, GL_FALSE, glm::value_ptr(GlutManager::GetMainCamera()->GetPerspective()));

	glm::mat4 v_inv = glm::inverse(GlutManager::GetMainCamera()->GetCameraMat());
	glUniformMatrix4fv(uniform_v_inv, 1, GL_FALSE, glm::value_ptr(v_inv));

}

bool MeshObject::Init(char* model_filename, char* vshader_filename, char* fshader_filename)
{
	ReadObjFile(model_filename);
	// mesh position initialized in init_view()

	BindBuffers();

	/* Compile and link shaders */
	GLint link_ok = GL_FALSE;
	GLint validate_ok = GL_FALSE;

	GLuint vs, fs;
	if ((vs = create_shader(vshader_filename, GL_VERTEX_SHADER)) == 0) return 0;
	if ((fs = create_shader(fshader_filename, GL_FRAGMENT_SHADER)) == 0) return 0;

	program = glCreateProgram();
	program = program;
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		return 0;
	}
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &validate_ok);
	if (!validate_ok) {
		fprintf(stderr, "glValidateProgram:");
	}

	const char* attribute_name;
	attribute_name = "v_coord";
	attribute_v_coord = glGetAttribLocation(program, attribute_name);
	if (attribute_v_coord == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		return 0;
	}
	attribute_name = "v_normal";
	attribute_v_normal = glGetAttribLocation(program, attribute_name);
	if (attribute_v_normal == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
		return 0;
	}
	const char* uniform_name;
	uniform_name = "m";
	uniform_m = glGetUniformLocation(program, uniform_name);
	if (uniform_m == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		return 0;
	}
	uniform_name = "v";
	uniform_v = glGetUniformLocation(program, uniform_name);
	if (uniform_v == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		return 0;
	}
	uniform_name = "p";
	uniform_p = glGetUniformLocation(program, uniform_name);
	if (uniform_p == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		return 0;
	}
	uniform_name = "m_3x3_inv_transp";
	uniform_m_3x3_inv_transp = glGetUniformLocation(program, uniform_name);
	if (uniform_m_3x3_inv_transp == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		return 0;
	}
	uniform_name = "v_inv";
	uniform_v_inv = glGetUniformLocation(program, uniform_name);
	if (uniform_v_inv == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
		return 0;
	}

	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5, 0.5, -0.5, 1.0,
		-0.5, 0.5, -0.5, 1.0,
		-0.5, -0.5, 0.5, 1.0,
		0.5, -0.5, 0.5, 1.0,
		0.5, 0.5, 0.5, 1.0,
		-0.5, 0.5, 0.5, 1.0,
	};
	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5, 2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLfloat
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;
	min_x = max_x = this->vertices[0].x;
	min_y = max_y = this->vertices[0].y;
	min_z = max_z = this->vertices[0].z;
	for (unsigned int i = 0; i < this->vertices.size(); i++) {
		if (this->vertices[i].x < min_x) min_x = this->vertices[i].x;
		if (this->vertices[i].x > max_x) max_x = this->vertices[i].x;
		if (this->vertices[i].y < min_y) min_y = this->vertices[i].y;
		if (this->vertices[i].y > max_y) max_y = this->vertices[i].y;
		if (this->vertices[i].z < min_z) min_z = this->vertices[i].z;
		if (this->vertices[i].z > max_z) max_z = this->vertices[i].z;
	}

	returnBB(glm::vec3(min_x, min_y, min_z), glm::vec3(max_x, max_y, max_z));

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.0, 20.0, 0.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	return 1;
}

void MeshObject::UpdateBoundingBox(float timeDelta)
{
	// Cube 1x1x1, centered on origin
	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5, 0.5, -0.5, 1.0,
		-0.5, 0.5, -0.5, 1.0,
		-0.5, -0.5, 0.5, 1.0,
		0.5, -0.5, 0.5, 1.0,
		0.5, 0.5, 0.5, 1.0,
		-0.5, 0.5, 0.5, 1.0,
	};
	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5, 
		2, 6, 3, 7
	};
	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLfloat
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;
	min_x = max_x = this->vertices[0].x;
	min_y = max_y = this->vertices[0].y;
	min_z = max_z = this->vertices[0].z;
	for (unsigned int i = 0; i < this->vertices.size(); i++) {
		if (this->vertices[i].x < min_x) min_x = this->vertices[i].x;
		if (this->vertices[i].x > max_x) max_x = this->vertices[i].x;
		if (this->vertices[i].y < min_y) min_y = this->vertices[i].y;
		if (this->vertices[i].y > max_y) max_y = this->vertices[i].y;
		if (this->vertices[i].z < min_z) min_z = this->vertices[i].z;
		if (this->vertices[i].z > max_z) max_z = this->vertices[i].z;
	}

	returnBB(glm::vec3(min_x, min_y, min_z), glm::vec3(max_x, max_y, max_z));	

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);
	calculateBottomFace();

}

