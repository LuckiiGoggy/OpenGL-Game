

#include "Quadtree.h"

Quadtree::Quadtree()
{
	MAX_OBJECTS = 10;
	MAX_LEVELS = 5;
}
Quadtree::Quadtree(int pLevel, Rect pBounds)
{
	MAX_OBJECTS = 10;
	MAX_LEVELS = 5;

	level = pLevel;
	objects = deque<Rect>();
	bounds = pBounds;
	//nodes = new Quadtree[4];
	nodes = (Quadtree**)malloc(sizeof(Quadtree) * 4);
}
void Quadtree::clear()
{

	objects.clear();

	for (int i = 0; i < numOfNodes; i++)
	{

		if (nodes[i] != NULL)
		{
			nodes[i]->clear();
			nodes[i] = NULL;

		}
	}
}
void Quadtree::split()
{
	int subWidth = (int)(bounds.getWidth() / 2);
	int subHeight = (int)(bounds.getHeight() / 2);
	int x = bounds.sx;
	int y = bounds.sy;

	nodes = (Quadtree**)malloc(sizeof(Quadtree) * 4);
	
	*nodes[0] = Quadtree(level+1, Rect(x + subWidth, y, subWidth, subHeight));
	*nodes[1] = Quadtree(level+1, Rect(x, y, subWidth, subHeight));
	*nodes[2] = Quadtree(level+1, Rect(x, y + subHeight, subWidth, subHeight));
	*nodes[3] = Quadtree(level+1, Rect(x + subWidth, y + subHeight, subWidth, subHeight));
}
/*
 * Determine which node the object belongs to. -1 means
 * object cannot completely fit within a child node and is part
 * of the parent node
 */
int Quadtree::getIndex(Rect pRect)
{
	int index = -1;
	double verticalMidpoint = bounds.sx + (bounds.getWidth() / 2);
	double horizontalMidpoint = bounds.sy + (bounds.getHeight() / 2);

	// Object can completely fit within the top quadrants
	bool topQuadrant = (pRect.sy < horizontalMidpoint && pRect.sy + pRect.getHeight() < horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (pRect.sy > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (pRect.sx < verticalMidpoint && pRect.sx + pRect.getWidth() < verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (pRect.sx > verticalMidpoint) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant) {
			index = 3;
		}
	}

	return index;
}
/*
 * Insert the object into the quadtree. If the node
 * exceeds the capacity, it will split and add all
 * objects to their corresponding nodes.


 The insert method is where everything comes together.
 The method first determines whether the node has any 
 child nodes and tries to add the object there. If there 
 are no child nodes or the object doesn’t fit in a child
 node, it adds the object to the parent node.

 Once the object is added, it determines whether the
 node needs to split by checking if the current number
 of objects exceeds the max allowed objects. 
 Splitting will cause the node to insert any object
 that can fit in a child node to be added to the child node;
 otherwise the object will stay in the parent node.
 */
void Quadtree::insert(Rect pRect)
{
	if (&nodes[0] != NULL) {
		int index = getIndex(pRect);

		if (index != -1) {
			nodes[index]->insert(pRect);

			return;
		}
	}

	//objects.add(pRect);
	objects.push_back(pRect);

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
		if (&nodes[0] == NULL) { 
			split(); 
		}

		int i = 0;
		while (i < objects.size()) {
			//int index = getIndex(objects.get(i));
			int index = getIndex(objects.at(i));
			if (index != -1) {
				//nodes[index]->insert(objects.remove(i));
				nodes[index]->insert(*(objects.erase(objects.begin() + i)));
			}
			else {
				i++;
			}
		}
	}
}
/*
 * Return all objects that could collide with the given object
 
 The final method of the quadtree is the 
 retrieve method. It returns all objects
 in all nodes that the given object could
 potentially collide with. This method is
 what helps to reduce the number of pairs
 to check collision against.
 */
list<Rect> Quadtree::retrieve(list<Rect> returnObjects, Rect pRect)
{
	int index = getIndex(pRect);
	if (index != -1 && nodes[0] != NULL) {
		nodes[index]->retrieve(returnObjects, pRect);
	}

	//returnObjects.addAll(objects);
	for ( deque<Rect>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		returnObjects.push_back(*it);
	}
	return returnObjects;
}