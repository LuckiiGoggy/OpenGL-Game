#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "openGL.h"
#include "Velocity.h"
#include "MeshObject.h"

class Projectile:public MeshObject {
public:
	Projectile();
	Projectile(glm::vec3 dir, glm::vec3 pos);
	Velocity v;
};

#endif
