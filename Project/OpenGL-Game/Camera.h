#ifndef CAMERA_H
#define CAMERA_H

#include "openGL.h"

#include "IGameObject.h"
#include "IMovable.h"
#include "IUpdateable.h"

#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies/glm/glm/gtx/rotate_vector.hpp"


class Camera: public IUpdateable
{
public:
	Camera();
	Camera(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 upDir);
	~Camera();

	virtual void Move(glm::vec3);
	virtual void Rotate(glm::vec3, float);
	virtual void Update(float timeDelta);
	virtual glm::mat4 GetPerspective();
	virtual glm::mat4 GetCameraMat();


private:
	glm::mat4 cameraMat;
	glm::mat4 perspMat;

	glm::vec3 cameraPos;
	glm::vec3 origLookAtPos; //relative to the camera pos
	glm::vec3 upDirection;

	glm::mat4 netTranslation;
	glm::mat4 netRotation;


};

#endif