#ifndef CAMERA_H
#define CAMERA_H

#include "openGL.h"

#include "IGameObject.h"
#include "IMovable.h"
#include "IUpdateable.h"

#include "Transform.h"


class Camera: public IGameObject, public Transform
{
public:
	Camera();
	Camera(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 upDir);
	~Camera();

	virtual void Update(float timeDelta);
	virtual void ClearRotation(void);
	virtual void SetCameraLookAt(glm::vec3);
	virtual glm::mat4 GetPerspective();
	virtual glm::mat4 GetCameraMat();

	virtual bool InView(glm::vec3);

	virtual void Move(float dX, float dY, float dZ, Space transformSpace = Space::Global);
	virtual void Move(glm::vec3 moveDelta, Space transformSpace = Space::Global);
	virtual void Rotate(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint = glm::vec3(0.0f), Space transformSpace = Space::Local);
	virtual void MoveTo(glm::vec3 pos);

protected:
	glm::mat4 cameraMat;
	glm::mat4 perspMat;

	glm::vec3 cameraPos;
	glm::vec3 origLookAtPos; //relative to the camera pos
	glm::vec3 upDirection;

	glm::vec3 GetRotationAxis(glm::vec3);
};

#endif