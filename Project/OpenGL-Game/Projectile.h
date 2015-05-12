#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "openGL.h"
#include "Velocity.h"
#include "MeshObject.h"
#include "RigidBody.h"

class Projectile:public RigidBody {
public:
	Projectile();
	Projectile(glm::mat4 &dir, glm::vec3 pos);
	Velocity* v;
};

#endif
