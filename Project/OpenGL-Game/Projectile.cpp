#include "Projectile.h"

Projectile::Projectile() {
	char* spear_filename = (char*) "../Assets/Models/spear.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.f.glsl";
	Init(spear_filename, v_shader_filename, f_shader_filename);
}

Projectile::Projectile(glm::vec3 dir, glm::vec3 pos) {
	char* spear_filename = (char*) "../Assets/Models/spear.obj";
	char* v_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.v.glsl";
	char* f_shader_filename = (char*) "../Assets/Shaders/gouraud-shading.f.glsl";
	Init(spear_filename, v_shader_filename, f_shader_filename);
	Move(pos);
	Rotate(dir, 0.0f);
}
