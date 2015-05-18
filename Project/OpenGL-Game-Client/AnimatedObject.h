#pragma once
#include "Transform.h"
#include "IGameObject.h"
#include "IRenderable.h"
#include "GameObjectContainer.h"
#include <vector>
#include <string>

class AnimatedObject : public IGameObject, public Transform, public IRenderable, public GameObjectContainer
{
public:
	AnimatedObject();
	~AnimatedObject();
	void Update(float timeDelta);
	void Render(void);

	/**Moves the GroupObject and all its members**/
	virtual void Move(float dX, float dY, float dZ, Space transformSpace = Space::Global);
	virtual void Move(glm::vec3 moveDelta, Space transformSpace = Space::Global);
	virtual void MoveTo(glm::vec3 pos);
	virtual void Rotate(float axisX, float axisY, float axisZ, float angle, glm::vec3 rotPoint = glm::vec3(0.0f), Space transformSpace = Space::Local);

private:
	int currentFrame;
	float timeBetweenFrames;
	float timeSinceLastFrame;

	std::vector<std::string> frameNames;
	
};

