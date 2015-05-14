#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "openGL.h"
#include "Velocity.h"
#include "MeshObject.h"

class Projectile:public MeshObject {
public:
	Projectile(glm::mat4 &dir, glm::vec3 pos, MeshObject* proj);
	void Update(float timeDelta);

	bool IsActive(void);

protected:
	float duration;
};

#endif
