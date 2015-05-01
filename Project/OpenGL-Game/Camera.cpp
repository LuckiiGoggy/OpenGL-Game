#include "Camera.h"


Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, -4.0f);
	origLookAtPos = glm::vec3(0.0f, 0.0f, 4.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	netTranslation  = glm::mat4(1.0);
	netRotation		= glm::mat4(1.0);

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

void Camera::Rotate(glm::vec3 rotateAxis, float angle){
	netRotation = glm::rotate(netRotation, angle, rotateAxis); 
	// where x, y, z is axis of rotation (e.g. 0 1 0)
}

void Camera::ClearRotation(void){
	netRotation = glm::mat4(1.0);
}

void Camera::Update(float timeDelta){

	glm::vec4 lookAtPos4(origLookAtPos, 1);
	lookAtPos4 = lookAtPos4 * netRotation;
	glm::vec3 lookAtPos(lookAtPos4);

	
	cameraMat = glm::lookAt(cameraPos, 
		cameraPos + lookAtPos, 
		upDirection);
		
	/*
	cameraMat = glm::lookAt(cameraPos,
		glm::vec3(0.0, 0.0, 0.0),
		upDirection);
		*/

	perspMat = glm::perspective(45.0f, 1.0f*glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT), 0.1f, 100.0f);
}

glm::mat4 Camera::GetPerspective(){
	return perspMat;
}

glm::mat4 Camera::GetCameraMat(){
	return cameraMat;
}