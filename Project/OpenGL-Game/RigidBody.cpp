#include "RigidBody.h"


RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

void RigidBody::AddForce(glm::vec3 force){
	forces.push_back(force);
}
void RigidBody::ClearForces(void){
	forces.empty();
}
std::vector<glm::vec3> RigidBody::GetForces(void){
	return forces;
}

void RigidBody::SetMass(float weight){
	mass = weight;
}
float RigidBody::GetMass(void){
	return mass;
}

void RigidBody::AddDeltaMove(glm::vec3 delta){
	this->deltaMove += delta;
}
void RigidBody::SetDeltaMove(glm::vec3 delta){
	this->deltaMove = delta;
}
void RigidBody::SubDeltaMove(glm::vec3 delta){
	this->deltaMove -= delta;
}
glm::vec3 RigidBody::GetDeltaMove(void){
	return deltaMove;
}

void RigidBody::ApplyDeltaMove(void){
	position += deltaMove;
	deltaMove = glm::vec3(0.0f);
}
glm::vec3 RigidBody::GetPosition(void){
	return position;
}

void RigidBody::SetName(std::string name){
	nameId = name;
}
std::string RigidBody::GetName(void){
	return nameId;
}

void RigidBody::SetBoundingBox(std::vector<glm::vec3> box){
	boundingBox = box;
}
std::vector<glm::vec3> RigidBody::GetBoundingBox(void){
	return boundingBox;
}

void RigidBody::SetRect(std::vector<glm::vec3> newRect){
	rect = newRect;
}
std::vector<glm::vec3> RigidBody::GetRect(void){
	return rect;
}