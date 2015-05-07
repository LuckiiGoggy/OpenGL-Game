#include "Camera.h"


Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 3.0f, 4.0f);
	origLookAtPos = glm::vec3(0.0f, 3.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	netTranslation  = glm::mat4(1.0);
	ClearRotation();

	perspMat = glm::perspective(45.0f, 1.0f*glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);

}


Camera::~Camera()
{
}

void Camera::Move(glm::vec3 moveDelta){

	glm::vec3 actMoveDelta = ApplyTransVec3(moveDelta, inverse(netRotation));

	cameraPos += actMoveDelta;
	origLookAtPos += actMoveDelta;

}

void Camera::UpdateNetRotation(void){
	netRotation = netRotationX * netRotationY * netRotationZ;
}

void Camera::RotateX(float angle){
	netRotationX = glm::rotate(netRotationX, angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::RotateY(float angle){
	netRotationY = glm::rotate(netRotationY, angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::RotateZ(float angle){
	netRotationZ = glm::rotate(netRotationZ, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::ClearRotation(void){
	netRotation = glm::mat4(1.0);
	netRotationX = glm::mat4(1.0);
	netRotationY = glm::mat4(1.0);
	netRotationZ = glm::mat4(1.0);
}


glm::vec3 Camera::GetRotationAxis(glm::vec3 axis){
	return ApplyTransVec3(axis, netRotation);
}

void Camera::Update(float timeDelta){
	UpdateNetRotation();
	glm::vec3 resUpDir = ApplyTransVec3(upDirection, inverse(netRotation));
	
	cameraMat = glm::lookAt(cameraPos, origLookAtPos, resUpDir);

	perspMat = glm::perspective(45.0f, 1.0f*glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);
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

void Camera::RotateAtLookAtX(float angle){
	glm::vec3 invLookAt;
	glm::vec3 moveVec;

	RotateX(angle);
	invLookAt = Inverse(origLookAtPos - cameraPos);

	cameraPos += glm::rotateX(invLookAt, angle) - invLookAt;
}

void Camera::RotateAtLookAtY(float angle){
	glm::vec3 invLookAt;
	glm::vec3 moveVec;

	RotateY(angle);
	invLookAt = Inverse(origLookAtPos - cameraPos);

	cameraPos += glm::rotateY(invLookAt, angle) - invLookAt;
}

void Camera::RotateAtLookAtZ(float angle){
	glm::vec3 invLookAt;

	glm::vec3 moveVec;

	RotateZ(angle);
	invLookAt = Inverse(origLookAtPos - cameraPos);

	cameraPos += glm::rotateZ(invLookAt, angle) - invLookAt;
}

glm::vec3 Camera::ApplyTransVec3(glm::vec3 point, glm::mat4 &transMat){
	glm::vec4 point4(point, 1);
	point4 = point4 * transMat;
	return glm::vec3(point4);
}

glm::vec3 Camera::Inverse(glm::vec3 vec){
	return glm::vec3(-vec.x, -vec.y, -vec.z);
}