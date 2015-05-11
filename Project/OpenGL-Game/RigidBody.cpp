#include "RigidBody.h"
//#define DEBUG_SCRIPT

/// CONSTRUCTORS 
RigidBody::RigidBody()
{
	id = -1;
	mass = 1;
	pMesh = new MeshObject();
}
RigidBody::RigidBody(int id_)
{
	id = id_;
	mass = 1;

	pMesh = new MeshObject();

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

	nameId = "RIGIDBODY";
}
RigidBody::RigidBody(float mass_, int id_)
{
	id = id_;
	mass = mass_;

	pMesh = new MeshObject();

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

	nameId = "RIGIDBODY";
}
RigidBody::RigidBody(float mass_, std::string nameID_, int id_)
{
	id = id_;
	mass = mass_;
	nameId = nameID_;

	pMesh = new MeshObject();

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;
}
RigidBody::RigidBody(MeshObject* mesh, int id_)
{
	id = id_;
	mass = 1;

	pMesh = new MeshObject();
	pMesh = mesh;

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

	nameId = "RIGIDBODY";
}
RigidBody::RigidBody(MeshObject* mesh, float mass_, int id_)
{
	id = id_;
	mass = mass_;

	pMesh = new MeshObject();
	pMesh = mesh;

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

	nameId = "RIGIDBODY";
}
RigidBody::RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_)
{
	id = id_;
	mass = mass_;
	nameId = nameID_;

	pMesh = new MeshObject();
	pMesh = mesh;

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;
}
RigidBody::RigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, int id_)
{
	id = id_;
	mass = 1;

	pMesh = new MeshObject();
	pMesh->Init(obj_filename, v_shader_filename, f_shader_filename);

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

	nameId = "RIGIDBODY";
}
RigidBody::RigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, float mass_, int id_)
{
	id = id_;
	mass = mass_;

	pMesh = new MeshObject();
	pMesh->Init(obj_filename, v_shader_filename, f_shader_filename);

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
	id_c = (const unsigned char *)intStr;

	nameId = "RIGIDBODY";
}
RigidBody::RigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, float mass_, std::string nameID_, int id_)
{
	id = id_;
	mass = mass_;
	nameId = nameID_;

	pMesh = new MeshObject();
	pMesh->Init(obj_filename, v_shader_filename, f_shader_filename);

	char *intStr = new char;
	_itoa_s(id, intStr, 3, 10);
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
void RigidBody::Update(float timeDelta){
	pMesh->Update(timeDelta);
}
void RigidBody::Render(){
	pMesh->Render();
#ifdef DEBUG_SCRIPT
	std::cout << "\n id " << this->id_c << "\n";
	std::cout << "BoundingBox v1 x: " << pMesh->boundingBox.v1.x << " y: " << pMesh->boundingBox.v1.y << " z: " << pMesh->boundingBox.v1.z << "\n";
	std::cout << "BoundingBox v2 x: " << pMesh->boundingBox.v2.x << " y: " << pMesh->boundingBox.v2.y << " z: " << pMesh->boundingBox.v2.z << "\n";
	std::cout << "BoundingBox v3 x: " << pMesh->boundingBox.v3.x << " y: " << pMesh->boundingBox.v3.y << " z: " << pMesh->boundingBox.v3.z << "\n";
	std::cout << "BoundingBox v4 x: " << pMesh->boundingBox.v4.x << " y: " << pMesh->boundingBox.v4.y << " z: " << pMesh->boundingBox.v4.z << "\n";
	std::cout << "BoundingBox v5 x: " << pMesh->boundingBox.v5.x << " y: " << pMesh->boundingBox.v5.y << " z: " << pMesh->boundingBox.v5.z << "\n";
	std::cout << "BoundingBox v6 x: " << pMesh->boundingBox.v6.x << " y: " << pMesh->boundingBox.v6.y << " z: " << pMesh->boundingBox.v6.z << "\n";
	std::cout << "BoundingBox v7 x: " << pMesh->boundingBox.v7.x << " y: " << pMesh->boundingBox.v7.y << " z: " << pMesh->boundingBox.v7.z << "\n";
	std::cout << "BoundingBox v8 x: " << pMesh->boundingBox.v8.x << " y: " << pMesh->boundingBox.v8.y << " z: " << pMesh->boundingBox.v8.z << "\n";
#endif
}
void RigidBody::SetBoundingBox(std::vector<glm::vec3> box){
	pMesh->boundingBox = BoundingBox(box[0], box[1], box[2], box[3], box[4],
		box[5], box[6], box[7]);

	pMesh->bottomFace = LocationRect(pMesh->boundingBox.v6.x, pMesh->boundingBox.v6.y,
		pMesh->boundingBox.v3.x, pMesh->boundingBox.v3.y);
	//rect = LocationRect(box.v2.x, box.v2.y, box.v7.x, box.v7.y);
	//rect = LocationRect(box.v1.x, box.v1.y, box.v3.x, box.v3.y);
}
void RigidBody::SetBoundingBox(BoundingBox box){
	pMesh->boundingBox = box;
	pMesh->bottomFace = LocationRect(box.v6.x, box.v6.y, box.v3.x, box.v3.y);
	//rect = LocationRect(box.v2.x, box.v2.y, box.v7.x, box.v7.y);
	//rect = LocationRect(box.v1.x, box.v1.y, box.v3.x, box.v3.y);
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
std::vector<glm::vec3> RigidBody::GetBoundingBox_vector(void){
	std::vector<glm::vec3> returnBox;
	BoundingBox Bbox = pMesh->boundingBox;
	returnBox.push_back(Bbox.v1);
	returnBox.push_back(Bbox.v2);
	returnBox.push_back(Bbox.v3);
	returnBox.push_back(Bbox.v4);
	returnBox.push_back(Bbox.v5);
	returnBox.push_back(Bbox.v6);
	returnBox.push_back(Bbox.v7);
	return returnBox;
}
BoundingBox* RigidBody::GetBoundingBox(void){
	return &pMesh->boundingBox;
}
void RigidBody::SetRect(LocationRect* newRect){
	pMesh->bottomFace = *newRect;
}
void RigidBody::SetRect(LocationRect newRect){
	pMesh->bottomFace = newRect;
}
void RigidBody::SetRect(int sx, int sy, int ex, int ey){
	pMesh->bottomFace = LocationRect(sx, sy, ex, ey, id);
}
void RigidBody::SetRect(int sx, int sy, int ex, int ey, int id_){
	pMesh->bottomFace = LocationRect(sx, sy, ex, ey, id_);
}
LocationRect RigidBody::GetRect_copy(void){
	return pMesh->bottomFace;
}
LocationRect* RigidBody::GetRect(void){
	return &pMesh->bottomFace;
}
void RigidBody::positionMesh()
{
	pMesh->Move(position.x, position.y, position.z);

	pMesh->bottomFace.move(position.x, position.z);

	pMesh->updateBoundingBox();
	//pMesh->boundingBox.translate(position.x, position.y, position.z);
}
void RigidBody::move(glm::vec3 v)
{
	float x = v.x; float y = v.y; float z = v.z;
	float x_ = ((float)x / (float)400);
	float y_ = ((float)y / (float)400);
	float z_ = ((float)z / (float)400);
	position.x += x_;// x;
	position.y += y_;// y;
	position.z += z_;// z;

	pMesh->Move(x_, y_, z_);

	pMesh->bottomFace.move(x_, z_);

	pMesh->updateBoundingBox();
	//pMesh->boundingBox.translate(x_, y_, z_);
}
void RigidBody::move(float x, float y, float z)
{
	float x_ = ((float)x / (float)400);
	float y_ = ((float)y / (float)400);
	float z_ = ((float)z / (float)400);
	position.x += x_;// x;
	position.y += y_;// y;
	position.z += z_;// z;

	pMesh->Move(x_, y_, z_);

	pMesh->bottomFace.move(x_, z_);

	pMesh->updateBoundingBox();
	//pMesh->boundingBox.translate(x_, y_, z_);
}
void RigidBody::move(float x, float y, float z, bool noChange)
{
	float x_ = x;
	float y_ = y;
	float z_ = z;
	position.x += x_;// x;
	position.y += y_;// y;
	position.z += z_;// z;

	pMesh->Move(x_, y_, z_);

	pMesh->bottomFace.move(x_, z_);

	pMesh->updateBoundingBox();
	//pMesh->boundingBox.translate(x_, y_, z_);
}