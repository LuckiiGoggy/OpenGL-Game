

#ifndef QUADTREE_H
#define QUADTREE_H

#include "RigidBody.h"
#include "RectObject.h"
#include "LocationRect.h"
#include "openGL.h"
#include <sstream>
#include <list>
#include <deque>
#include <vector>

using namespace std;

class Quadtree
{
public:
	Quadtree();
	//~Quadtree();
	Quadtree(int pLevel, Rect pBounds);

	void clear();
	void split();
	//int getIndex(Rect pRect);
	int getIndex(RectObject pRect);
	//int getIndex(RigidBody pRect);
	int getIndex(RigidBody* pRect);
	int getIndex(LocationRect pRect);
	//void insert(Rect* pRect);
	void insert(RectObject* pRect);
	void insert(RigidBody* pRect);
	//list<Rect*>* retrieve(list<Rect*> *returnObjects, Rect* pRect);
	list<RectObject*>* retrieve(list<RectObject*> *returnObjects, RectObject* pRect);
	list<RigidBody*>* retrieve(list<RigidBody*> *returnObjects, RigidBody* pRect);

	void draw();
	void draw(bool DRAW_CONTAINED_ITEM_ID);

	void drawRectBounds(Rect r, glm::vec3 color);
	glm::vec3 calcRelativePoints2D(int x, int y, int screenWidth, int screenHeight);



	int screenW;
	int screenH;
	glm::vec3 black;
	glm::vec3 red;

	int MAX_OBJECTS;
	int MAX_LEVELS;

	int level;

	//deque<Rect*> objects;
	deque<RectObject*> rectObjects;
	deque<RigidBody*> rigidObjects;
	Rect bounds;

	int numOfNodes;
	Quadtree** nodes;
	//vector<Quadtree*> nodes;
};

#endif