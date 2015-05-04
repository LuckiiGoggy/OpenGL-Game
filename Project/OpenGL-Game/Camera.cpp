#include "Camera.h"


Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, -4.0f);
	origLookAtPos = glm::vec3(0.0f, 0.0f, 4.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	netTranslation  = glm::mat4(1.0);
	ClearRotation();

	cameraMat = glm::lookAt(
		glm::vec3(0.0, 0.0, 4.0),   // eye
		glm::vec3(0.0, 0.0, 0.0),   // direction
		glm::vec3(0.0, 1.0, 0.0));  // up

	perspMat = glm::perspective(45.0f, 1.0f*glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);

}


Camera::~Camera()
{
}

void Camera::Move(glm::vec3 moveDelta){
	glm::vec4 moveDelta4(moveDelta, 1);
	moveDelta4 = moveDelta4 * netRotation;
	glm::vec3 actMoveDelta(moveDelta4);

	cameraPos += actMoveDelta;
}

void Camera::UpdateNetRotation(void){
	netRotation = netRotationX * netRotationY * netRotationZ;
}

void Camera::RotateX(float angle){
	netRotationX = glm::rotate(netRotationX, angle, GetRotationAxis(glm::vec3(1.0f, 0.0f, 0.0f)));
	UpdateNetRotation();
}

void Camera::RotateY(float angle){
	netRotationX = glm::rotate(netRotationX, angle, GetRotationAxis(glm::vec3(0.0f, 1.0f, 0.0f)));
	UpdateNetRotation();
}

void Camera::RotateZ(float angle){
	netRotationX = glm::rotate(netRotationX, angle, GetRotationAxis(glm::vec3(0.0f, 0.0f, 1.0f)));
	UpdateNetRotation();
}

void Camera::ClearRotation(void){
	netRotation = glm::mat4(1.0);
	netRotationX = glm::mat4(1.0);
	netRotationY = glm::mat4(1.0);
	netRotationZ = glm::mat4(1.0);
}


glm::vec3 Camera::GetRotationAxis(glm::vec3 axis){
	glm::vec4 axis4(axis, 1);
	axis4 = axis4 * netRotation;
	return glm::vec3(axis4);

	//return axis;
}

void Camera::Update(float timeDelta){

	glm::vec4 lookAtPos4(origLookAtPos, 1);
	lookAtPos4 = lookAtPos4 * netRotation;
	glm::vec3 lookAtPos(lookAtPos4);

	glm::vec4 upDirection4(upDirection, 1);
	upDirection4 = upDirection4 * netRotation;
	glm::vec3 resUpDir(upDirection4);

	
	cameraMat = glm::lookAt(cameraPos, 
		cameraPos + lookAtPos, 
		resUpDir);

	perspMat = glm::perspective(45.0f, 1.0f*glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);
}

glm::mat4 Camera::GetPerspective(){
	return perspMat;
}

glm::mat4 Camera::GetCameraMat(){
	return cameraMat;
}