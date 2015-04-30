#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <string>
#include <vector>
#include "Dependencies\glm\glm\glm.hpp"


class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	void AddForce(glm::vec3);
	void ClearForces(void);
	std::vector<glm::vec3> GetForces(void);

	void SetMass(float weight);
	float GetMass(void);

	void AddDeltaMove(glm::vec3);
	void SetDeltaMove(glm::vec3);
	void SubDeltaMove(glm::vec3);
	glm::vec3 GetDeltaMove(void);

	void ApplyDeltaMove(void);
	glm::vec3 GetPosition(void);

	void SetName(std::string);
	std::string GetName(void);

	void SetBoundingBox(std::vector<glm::vec3>);
	std::vector<glm::vec3> GetBoundingBox(void);

	void SetRect(std::vector<glm::vec3>);
	std::vector<glm::vec3> GetRect(void);

private:
	std::vector<glm::vec3> forces;
	float mass;
	glm::vec3 deltaMove;
	glm::vec3 position;
	std::string nameId;

	std::vector<glm::vec3> boundingBox;
	std::vector<glm::vec3> rect;
};

#endif
