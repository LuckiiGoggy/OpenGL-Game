#include "Camera.h"
#include <iostream>

Camera::Camera()
{
	position = glm::vec3(0.0f, 6.0f, 8.0f);
	origLookAtPos = glm::vec3(0.0f, 3.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	netTranslation  = glm::mat4(1.0);
	ClearRotation();

	perspMat = glm::perspective(45.0f, 1.0f*glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);

}


Camera::~Camera()
{
}

void Camera::ClearRotation(void){
	netRotation = glm::mat4(1.0);
}


glm::vec3 Camera::GetRotationAxis(glm::vec3 axis){
	return ApplyTransVec3(axis, netRotation);
}

void Camera::Update(float timeDelta){
	//UpdateNetRotation();
	glm::vec3 resUpDir = ApplyTransVec3(upDirection, netRotation);
	
	cameraMat = glm::lookAt(position, origLookAtPos, resUpDir);

	perspMat = glm::perspective(45.0f, 1.0f*glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);

}

bool Camera::InView(glm::vec3 pos){

	if (glm::length(pos - position) < glm::length(origLookAtPos - position)){
		return true;
	}

	return false;
}

glm::mat4 Camera::GetPerspective(){
	return perspMat;
}

glm::mat4 Camera::GetCameraMat(){
	return cameraMat;
}

void Camera::SetCameraLookAt(glm::vec3 lookat){
	origLookAtPos = lookat;
}

void Camera::Move(float dX, float dY, float dZ, Space transformSpace){
	glm::vec3 moveDelta = glm::vec3(dX, dY, dZ);
	//Transform::Move(moveDelta, transformSpace);
	switch (transformSpace){
	case Local:
		moveDelta = ApplyTransVec3(moveDelta, netRotation);
	case Global:
		origLookAtPos += moveDelta;
		position += moveDelta;
		break;
	}
}
void Camera::Move(glm::vec3 moveDelta, Space transformSpace){
	//Transform::Move(moveDelta, transformSpace);
	switch (transformSpace){
	case Local:
		moveDelta = ApplyTransVec3(moveDelta, netRotation);
	case Global:
		origLookAtPos += moveDelta;
		position += moveDelta;
		break;
	}
}
void Camera::Rotate(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint, Space transformSpace){
	glm::vec3 rotateAxis = glm::vec3(axisX, axisY, axisZ);
	glm::vec3 moveDelta;


	switch (transformSpace)
	{
	case Local:
		netRotation = glm::rotate(netRotation, angle, rotateAxis); // where x, y, z is axis of rotation (e.g. 0 1 0)
		break;
	case Global:
		glm::vec3 dstFromPointStart = position - rotPoint;
		glm::vec3 dstFromPointEnd = ApplyTransVec3(dstFromPointStart, glm::rotate(angle, rotateAxis));
		netRotation = glm::rotate(netRotation, angle, rotateAxis);
		position += (dstFromPointEnd - dstFromPointStart);
		break;
	}



}

void Camera::MoveTo(glm::vec3 pos)
{
	position -= origLookAtPos - glm::vec3(0.0f, 3.0f, 0.0f);
	position += pos;
	origLookAtPos = pos + glm::vec3(0.0f, 3.0f, 0.0f);
}
