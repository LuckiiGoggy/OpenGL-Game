#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_
#include "openGL.h"
#include "Velocity.h"
#include "MeshObject.h"

class Projectile:public MeshObject {
public:
	Projectile(glm::mat4 &dir, glm::vec3 pos, MeshObject* proj, int shooterId);
	Projectile(glm::mat4 &dir, glm::vec3 pos, MeshObject* proj);
	Projectile(glm::mat4 &dir, glm::vec3 pos, int shooterId);
	Projectile(glm::mat4 &dir, glm::vec3 pos);
	void Update(float timeDelta);

	bool IsActive(void);

	int GetShooter(void);
	void SetShooter(int);

protected:
	float duration;
	int shooterObjId;
};

#endif
