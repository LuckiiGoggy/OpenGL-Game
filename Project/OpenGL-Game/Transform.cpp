#include "Transform.h"


Transform::Transform(void)
{
	position = glm::vec3(0.0f);

	netTransformations = glm::mat4(1.0f);
	netTranslation = glm::mat4(1.0f);
	netRotation = glm::mat4(1.0f);
	netScale = glm::mat4(1.0f);
}

void Transform::UpdateNetTransformations(void){
	netTransformations = netTranslation * netRotation * netScale;
}

void Transform::Move(float dX, float dY, float dZ, Space transformSpace){
	glm::vec3 moveDelta(dX, dY, dZ);

	switch (transformSpace){
	case Local:
		moveDelta = ApplyTransVec3(moveDelta, inverse(netRotation));
	case Global:
		netTranslation = glm::translate(netTranslation, moveDelta);
		position += moveDelta;
		break;
	}
}

void Transform::Move(glm::vec3 moveDelta, Space transformSpace){
	switch (transformSpace){
	case Local:
		moveDelta = ApplyTransVec3(moveDelta, netRotation);
	case Global:
		netTranslation = glm::translate(netTranslation, moveDelta);
		position += moveDelta;
		break;
	}
}

void Transform::Rotate(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint, Space transformSpace){
	glm::vec3 rotateAxis = glm::vec3(axisX, axisY, axisZ);


	switch (transformSpace)
	{
	case Local:
		netRotation = glm::rotate(netRotation, angle, rotateAxis); // where x, y, z is axis of rotation (e.g. 0 1 0)
		break;
	case Global:
		glm::vec3 dstFromPointStart = position - rotPoint;
		glm::vec3 dstFromPointEnd = ApplyTransVec3(dstFromPointStart, glm::rotate(angle, rotateAxis));
		//glm::vec3 dstFromPointEnd = glm::rotateY(dstFromPointStart, angle);
		Move(dstFromPointEnd - dstFromPointStart, transformSpace);
		netRotation = glm::rotate(netRotation, angle, rotateAxis);
		break;
	}


}

glm::vec3 Transform::Position(void){
	return position;
}

void Transform::Scale(float scaleX, float scaleY, float scaleZ, Space transformSpace){
	netScale = glm::scale(netScale, glm::vec3(scaleX, scaleY, scaleZ));

}

glm::vec3 Transform::Inverse(glm::vec3 vec){
	return glm::vec3(-vec.x, -vec.y, -vec.z);
}

glm::vec3 Transform::ApplyTransVec3(glm::vec3 point, glm::mat4 &transMat){
	glm::vec4 point4(point, 1);
	point4 = transMat * point4;
	return glm::vec3(point4);
}

