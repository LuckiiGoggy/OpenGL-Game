#include "Projectile.h"
#include "ServerMain.h"


Projectile::Projectile(glm::mat4 &dir, glm::vec3 pos) {
	netRotation = dir;
	Move(pos);
	glm::vec3 offset(0.0f, 0.1f, -2.5f);
	Move(offset, Transform::Space::Local);
	duration = 1;
}

Projectile::Projectile(glm::mat4 &dir, glm::vec3 pos, MeshObject* proj) : MeshObject(*proj) {
	netRotation = dir;
	Move(pos);
	glm::vec3 offset(0.0f, 0.1f, -2.5f);
	Move(offset, Transform::Space::Local);
	duration = 1;
}

void Projectile::Update(float timeDelta)
{
	duration -= timeDelta;

	MeshObject::Update(timeDelta);
}

bool Projectile::IsActive(void)
{
	return (duration > 0);
}
