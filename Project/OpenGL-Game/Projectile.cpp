#include "Projectile.h"

Projectile::Projectile() {
	
}

Projectile::Projectile(glm::vec3 dir, glm::vec3 pos) {
	MeshObject::Move(pos);
	MeshObject::Rotate(dir, 0.0f);
}
