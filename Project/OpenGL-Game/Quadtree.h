

#ifndef QUADTREE_H
#define QUADTREE_H

#include "Rect.h"
#include <list>
#include <deque>

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
	list<Rect> retrieve(list<Rect> returnObjects, Rect pRect);

	int MAX_OBJECTS;
	int MAX_LEVELS;

	int level;

	deque<Rect> objects;
	Rect bounds;

	int numOfNodes;
	Quadtree **nodes;
};

#endif