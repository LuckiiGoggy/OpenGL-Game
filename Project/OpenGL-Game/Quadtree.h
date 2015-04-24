

#ifndef QUADTREE_H
#define QUADTREE_H

#include "Rect.h"
#include "openGL.h"
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
	int getIndex(Rect pRect);
	void insert(Rect pRect);
	list<Rect>* retrieve(list<Rect> *returnObjects, Rect pRect);

	void draw();

	void drawRectBounds(Rect r, glm::vec3 color);
	glm::vec3 calcRelativePoints2D(int x, int y, int screenWidth, int screenHeight);

	

	int screenW;
	int screenH;
	glm::vec3 black;
	glm::vec3 red;

	int MAX_OBJECTS;
	int MAX_LEVELS;

	int level;

	deque<Rect> objects;
	Rect bounds;

	int numOfNodes;
	Quadtree** nodes;
	//vector<Quadtree*> nodes;
};

#endif