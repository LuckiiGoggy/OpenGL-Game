#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <string>
#include <vector>
#include "Dependencies\glm\glm\glm.hpp"

//
#include "Velocity.h"
#include "MeshObject.h" //Includes BoundingBox and LocationRect
//


class RigidBody : public IGameObject, public IRenderable
{
public:
	RigidBody();
	RigidBody(int id_);
	RigidBody(float mass_, int id_);
	RigidBody(float mass_, std::string nameID_, int id_);
	RigidBody(MeshObject* mesh, int id_);
	RigidBody(MeshObject* mesh, float mass_, int id_);
	RigidBody(MeshObject* mesh, float mass_, std::string nameID_, int id_);
	RigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, int id_);
	RigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, float mass_, int id_);
	RigidBody(char* obj_filename, char* v_shader_filename, char* f_shader_filename, float mass_, std::string nameID_, int id_);

	~RigidBody();

	void Render(void);//calls pMesh->Render()
	virtual void Update(float timeDelta);

	void SetName(std::string);  //set this object's string ID
	std::string GetName(void);  //return this object's string ID

	void SetMass(float weight); //set this object's mass
	float GetMass(void);		//return this object's mass

	//Type
	bool isProjectile();
	bool isPlayer();
	bool isLevelObject();
	bool isEnvironment();
	int getType();
	void setType(int type_);

	//Velocities
	void addVelocity(Velocity* velocity);
	void ClearVelocities(void);
	std::vector<Velocity*>* GetVelocities(void);

	//Movement
	void AddDeltaMove(glm::vec3);
	void SetDeltaMove(glm::vec3);
	void SubDeltaMove(glm::vec3);
	glm::vec3 GetDeltaMove(void);
	void ApplyDeltaMove(void);
	glm::vec3 GetPosition(void);
	void SetPosition(glm::vec3 pos);
	void SetPosition(float x, float y, float z);

	void move(glm::vec3);
	void move(float x, float y, float z);
	void move(float x, float y, float z, bool noChange);

	//Location Rect
	void SetRect(LocationRect rect);
	void SetRect(LocationRect* rect);
	void SetRect(int sx, int sy, int ex, int ey);		  //Creates a new LocationRect
	void SetRect(int sx, int sy, int ex, int ey, int id); //Creates a new LocationRect
	LocationRect GetRect_copy(void);
	LocationRect* GetRect(void);

	//Bounding Box
	void SetBoundingBox(std::vector<glm::vec3>);		//Creates a new BoundingBox
	void SetBoundingBox(BoundingBox box);
	BoundingBox* GetBoundingBox(void);					//returns &Bbox
	std::vector<glm::vec3> GetBoundingBox_vector(void); //returns a vector of Bbox's verticies

	//Physics and Collisions 
	std::vector<Velocity*> velocities;					//list of velocities effecting this object
	float mass;
	int id;
	const unsigned char * id_c;

	//Mesh
	void positionMesh();
	MeshObject* pMesh;

private:

	glm::vec3 deltaMove;
	glm::vec3 position;
	std::string nameId;
	int type;//1 = projectile, 2 = player, 3 = level object (dynamic), 4 = environment (static)
};
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
#endif
