#include "RigidBody.h"
//#define DEBUG_SCRIPT

/// CONSTRUCTORS 
RigidBody::RigidBody()
{
	id = -1;
	mass = 1;
	type = 1;
	pTrans = new Transform();
	boundingBox = new BoundingBox();
}
RigidBody::RigidBody(BoundingBox* box, Transform* trans, float mass_, std::string nameID_)
{
	id = -1;
	mass = mass_;
	nameId = nameID_;
	type = 1;

	boundingBox = new BoundingBox();
	boundingBox = box;

	pTrans = new Transform();
	pTrans = trans;

	char *intStr = new char;
	_itoa_s(id, intStr, 5, 10);
	id_c = (const unsigned char *)intStr;
}
RigidBody::RigidBody(BoundingBox* box, Transform* trans, float mass_, std::string nameID_, int id_)
{
	id = id_;
	mass = mass_;
	nameId = nameID_;
	type = 1;

	boundingBox = new BoundingBox();
	boundingBox = box;

	pTrans = new Transform();
	pTrans = trans;

	char *intStr = new char;
	_itoa_s(id, intStr, 5, 10);
	id_c = (const unsigned char *)intStr;
}
RigidBody::RigidBody(BoundingBox* box, Transform* trans, float mass_, int type_, std::string nameID_, int id_)
{
	id = id_;
	mass = mass_;
	nameId = nameID_;

	type = type_;

	boundingBox = new BoundingBox();
	boundingBox = box;

	pTrans = new Transform();
	pTrans = trans;

	char *intStr = new char;
	_itoa_s(id, intStr, 5, 10);
	id_c = (const unsigned char *)intStr;
}
RigidBody::RigidBody(BoundingBox* box, Transform* trans, float mass_, int type_, std::string nameID_)
{
	id = -1;
	mass = mass_;
	nameId = nameID_;

	type = type_;

	boundingBox = new BoundingBox();
	boundingBox = box;

	pTrans = new Transform();
	pTrans = trans;

	char *intStr = new char;
	_itoa_s(id, intStr, 5, 10);
	id_c = (const unsigned char *)intStr;
}

///END OF CONSTRUCTORS 
RigidBody::~RigidBody()
{
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
void RigidBody::SetPosition(glm::vec3 pos){
	position = pos;
}
void RigidBody::SetPosition(float x, float y, float z){
	position.x = x;
	position.y = y;
	position.z = z;
}

void RigidBody::SetName(std::string name){
	nameId = name;
}
std::string RigidBody::GetName(void){
	return nameId;
}


bool RigidBody::isProjectile()
{
	if (type == 1)
	{
		return true;
	}
	return false;
}
bool RigidBody::isPlayer()
{
	if (this->type == 2)
	{
		return true;
	}
	return false;
}
bool RigidBody::isLevelObject()
{
	if (this->type == 3)
	{
		return true;
	}
	return false;
}
bool RigidBody::isEnvironment()
{
	if (this->type == 4)
	{
		return true;
	}
	return false;
}
int RigidBody::getType()
{
	return this->type;
}
void RigidBody::setType(int type_)
{
	this->type = type_;
}

void RigidBody::addVelocity(Velocity* velocity){
	velocities.push_back(velocity);
}
void RigidBody::ClearVelocities(void){
	velocities.empty();
}
std::vector<Velocity*>* RigidBody::GetVelocities(void){
	return &velocities;
}
void RigidBody::updateBoundingBox()
{
	//Apply world transformation to bounding box
	//*
	glm::vec4 v1_world = (this->pTrans->NetTranslation() * glm::vec4(boundingBox->v1.x, boundingBox->v1.y, boundingBox->v1.z, 1));
	glm::vec4 v2_world = (this->pTrans->NetTranslation() * glm::vec4(boundingBox->v2.x, boundingBox->v2.y, boundingBox->v2.z, 1));
	glm::vec4 v3_world = (this->pTrans->NetTranslation() * glm::vec4(boundingBox->v3.x, boundingBox->v3.y, boundingBox->v3.z, 1));
	glm::vec4 v4_world = (this->pTrans->NetTranslation() * glm::vec4(boundingBox->v4.x, boundingBox->v4.y, boundingBox->v4.z, 1));
	glm::vec4 v5_world = (this->pTrans->NetTranslation() * glm::vec4(boundingBox->v5.x, boundingBox->v5.y, boundingBox->v5.z, 1));
	glm::vec4 v6_world = (this->pTrans->NetTranslation() * glm::vec4(boundingBox->v6.x, boundingBox->v6.y, boundingBox->v6.z, 1));
	glm::vec4 v7_world = (this->pTrans->NetTranslation() * glm::vec4(boundingBox->v7.x, boundingBox->v7.y, boundingBox->v7.z, 1));
	glm::vec4 v8_world = (this->pTrans->NetTranslation() * glm::vec4(boundingBox->v8.x, boundingBox->v8.y, boundingBox->v8.z, 1));
	//*/

	//*
	boundingBox->v1 = glm::vec3(v1_world);
	boundingBox->v2 = glm::vec3(v2_world);
	boundingBox->v3 = glm::vec3(v3_world);
	boundingBox->v4 = glm::vec3(v4_world);
	boundingBox->v5 = glm::vec3(v5_world);
	boundingBox->v6 = glm::vec3(v6_world);
	boundingBox->v7 = glm::vec3(v7_world);
	boundingBox->v8 = glm::vec3(v8_world);//*/

	//Calculate the updated bottomFace of the bounding box
	//calculateBottomFace();

	//Recalculate the directional radius of the bounding box
	boundingBox->refresh();
}
void RigidBody::SetBoundingBox(BoundingBox* box){
	boundingBox = box;
	/*
	EVERYTHING IS COUNTER CLOCKWISE

	v1 v4     v5  v8
	v2 v3     v6  v7

	Front Face  = v1 v2 v3 v4
	Back Face   = v5 v6 v7 v8
	Left Face   = v1 v2 v6 v5
	Right Face  = v4 v3 v7 v8
	Bottom Face = v2 v6 v7 v3
	Top Face    = v5 v1 v4 v8

	Front Face Midpoint = v1  vs  v4
	Back Face Midpoint  = v5  vs  v7

	//*/
}

BoundingBox* RigidBody::GetBoundingBox(void){
	return boundingBox;
}

void RigidBody::move(glm::vec3 v)
{
	float x = v.x; float y = v.y; float z = v.z;

	pTrans->Move(x, y, z, Transform::Local);
}
void RigidBody::move(float x, float y, float z)
{
	pTrans->Move(x, y, z, Transform::Local);

	updateBoundingBox();
}
void RigidBody::move(float x, float y, float z, bool noChange)
{
	pTrans->Move(x, y, z);

	updateBoundingBox();
}

glm::vec3 RigidBody::NetVelocity(void)
{
	glm::vec3 netVelocity(0.0f);
	for (size_t i = 0; i < velocities.size(); i++)
	{
		Velocity *velo = velocities[i];
		if (velo->velocityType != 3)
		{
			glm::vec3 vel(velo->x, velo->y, velo->z);

			vel = Transform::ApplyTransVec3(vel, pTrans->NetRotation());

			netVelocity += vel;
		}
	}

	std::cout << "\nNETVELOCITY: " << netVelocity.x << "," << netVelocity.y << "," << netVelocity.z;
	return netVelocity;
}

glm::vec3 RigidBody::NetVelocityX(void)
{
	glm::vec3 netVelocity(0.0f);
	for (size_t i = 0; i < velocities.size(); i++)
	{
		Velocity *velo = velocities[i];
		if (velo->velocityType != 3)
		{
			glm::vec3 vel(velo->x, velo->y, velo->z);

			//vel = Transform::ApplyTransVec3(vel, pMesh->NetRotation());

			netVelocity += vel;
		}
	}

	std::cout << "\nNETVELOCITY: " << netVelocity.x << "," << netVelocity.y << "," << netVelocity.z;
	return netVelocity;
}
