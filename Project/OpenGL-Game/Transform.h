#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "Dependencies\glm\glm\glm.hpp"
#include "Dependencies/glm/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/glm/gtc/type_ptr.hpp"
#include "Dependencies/glm/glm/gtx/rotate_vector.hpp"


class Transform
{

public:
	enum Axis{ X, Y, Z };
	enum Space{ Local, Global };
	
	Transform(void);

	virtual void Move(float dX, float dY, float dZ, Space transformSpace = Space::Global);
	virtual void Move(glm::vec3 moveDelta, Space transformSpace = Space::Global);
	virtual void Rotate(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint = glm::vec3(0.0f), Space transformSpace = Space::Local);
	virtual void Scale(float scaleX, float scaleY, float scaleZ, Space transformSpace = Space::Local);

	static glm::vec3 ApplyTransVec3(glm::vec3 point, glm::mat4 &transMat);
	static glm::vec3 Inverse(glm::vec3 vec);


	virtual glm::mat4& NetTranslation(void);
	virtual glm::mat4& NetRotation(void);
	virtual glm::mat4& NetScale(void);

	glm::vec3 Position(void);
	void* operator new(size_t);
	void  operator delete(void*);
protected:
	glm::vec3 position;

	glm::mat4 netTransformations;
	glm::mat4 netTranslation;
	glm::mat4 netRotation;
	glm::mat4 netScale;

	void UpdateNetTransformations(void);

};

#endif