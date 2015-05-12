#include "Projectile.h"

Projectile::Projectile() {
	
}

Projectile::Projectile(glm::mat4 &dir, glm::vec3 pos, MeshObject* proj) : MeshObject(*proj) {
	netRotation = dir;
	Move(pos);
	glm::vec3 offset(0.0f, 0.1f, -2.5f);
	Move(offset, Transform::Space::Local);
}
