#include "Projectile.h"

Projectile::Projectile() {
	RigidBody::RigidBody();
	char* spear_filename = (char*) "../Assets/Models/spear.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.f.glsl";
	Init(spear_filename, v_shader_filename, f_shader_filename);
}

Projectile::Projectile(glm::mat4 &dir, glm::vec3 pos) {
	char* spear_filename = (char*) "../Assets/Models/spear.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.f.glsl";
	Init(spear_filename, v_shader_filename, f_shader_filename);

	NetRotation() = dir;
	Move(pos);
	glm::vec3 offset(0.0f, 0.1f, -0.5f);
	Move(offset, Transform::Space::Local);
	glm::vec3 vdir = glm::vec3(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) * dir);
}
