#ifndef CAMERA_H
#define CAMERA_H

#include "openGL.h"

#include "IGameObject.h"
#include "IMovable.h"
#include "IUpdateable.h"

#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies/glm/glm/gtx/rotate_vector.hpp"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"


class Camera: public IGameObject, public IMovable
{
public:
	Camera();
	Camera(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 upDir);
	~Camera();

	virtual void Move(glm::vec3);
	virtual void RotateX(float);
	virtual void RotateY(float);
	virtual void RotateZ(float);
	virtual void Update(float timeDelta);
	virtual void ClearRotation(void);
	virtual void SetCameraLookAt(glm::vec3);
	virtual glm::mat4 GetPerspective();
	virtual glm::mat4 GetCameraMat();

	virtual void RotateAtLookAtX(float angle);
	virtual void RotateAtLookAtY(float angle);
	virtual void RotateAtLookAtZ(float angle);


protected:
	glm::mat4 cameraMat;
	glm::mat4 perspMat;

	glm::vec3 cameraPos;
	glm::vec3 origLookAtPos; //relative to the camera pos
	glm::vec3 upDirection;

	glm::mat4 netTranslation;
	glm::mat4 netRotation;
	glm::mat4 netRotationX;
	glm::mat4 netRotationY;
	glm::mat4 netRotationZ;

	void UpdateNetRotation(void);
	glm::vec3 GetRotationAxis(glm::vec3);

	glm::vec3 ApplyTransVec3(glm::vec3 point, glm::mat4 &transMat);
	glm::vec3 Inverse(glm::vec3);
};

#endif