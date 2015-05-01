

#include "Quadtree.h"

Quadtree::Quadtree()
{
	MAX_OBJECTS = 2;
	MAX_LEVELS = 5;

	level = 1;
	//objects = deque<Rect*>();
	rectObjects = deque<RectObject*>();

	numOfNodes = 4;

	screenW = 400;
	screenH = 400;
	black = glm::vec3(0.0f, 0.0f, 0.0f);
	red = glm::vec3(1.0f, 0.0f, 0.0f);

	nodes = nullptr;
}
Quadtree::Quadtree(int pLevel, Rect pBounds)
{
	MAX_OBJECTS = 1;
	MAX_LEVELS = 7;

	level = pLevel;
	//objects = deque<Rect*>();
	rectObjects = deque<RectObject*>();
	bounds = pBounds;

	numOfNodes = 4;

	screenW = 400;
	screenH = 400;
	black = glm::vec3(0.0f, 0.0f, 0.0f);
	red = glm::vec3(1.0f, 0.0f, 0.0f);

	nodes = nullptr;
}
void Quadtree::clear()
{
	//objects.clear();
	rectObjects.clear();

	if (nodes != nullptr)
	{
		for (int i = 0; i < numOfNodes; i++)
		{
			if (nodes[i] != nullptr)
			{
				nodes[i]->clear();
				delete(nodes[i]);
			}
		}
	}
	
	nodes = nullptr;
}
void Quadtree::split()
{
	int subWidth = (int)(bounds.getWidth() / 2);
	int subHeight = (int)(bounds.getHeight() / 2);
	int x = bounds.sx;
	int y = bounds.sy;

	//int ex = bounds.ex;
	//int ey = bounds.ey;

	nodes = new Quadtree*[4];
	
	/*
	nodes[0] = new Quadtree(level+1, Rect(x + subWidth, y, subWidth, subHeight));
	nodes[1] = new Quadtree(level+1, Rect(x, y, subWidth, subHeight));
	nodes[2] = new Quadtree(level+1, Rect(x, y + subHeight, subWidth, subHeight));
	nodes[3] = new Quadtree(level+1, Rect(x + subWidth, y + subHeight, subWidth, subHeight));//*/

	//*
	nodes[3] = new Quadtree(level+1, Rect(x + subWidth, y + subHeight, x + subWidth + subWidth, y + subHeight + subHeight));
	nodes[2] = new Quadtree(level+1, Rect(x, y + subHeight, x + subWidth, y));
	nodes[1] = new Quadtree(level+1, Rect(x, y, x + subWidth, y + subHeight));
	nodes[0] = new Quadtree(level+1, Rect(x + subWidth, y, x + subWidth + subWidth,y + subHeight));
	//*/
}
/*
 * Determine which node the object belongs to. -1 means
 * object cannot completely fit within a child node and is part
 * of the parent node
 */
/*int Quadtree::getIndex(Rect pRect)
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
}//*/
int Quadtree::getIndex(RectObject pRect)
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
/*void Quadtree::insert(Rect *pRect)
{
	if (nodes != nullptr)
	{
		if (nodes[0] != nullptr) {
			int index = getIndex(*pRect);

			if (index != -1) {
				nodes[index]->insert(pRect);

				return;
			}
		}
	}
	
	objects.push_back(pRect);

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
		if (nodes == nullptr) {
			split(); 
		}
		

		int i = 0;
		while (i < objects.size()) {
			int index = getIndex(*objects.at(i));
			if (index != -1) {
				nodes[index]->insert(objects[i]);
				objects.erase(objects.begin() + i);
			}
			else {
				i++;
			}
		}
	}
}//*/
void Quadtree::insert(RectObject *pRect)
{
	if (nodes != nullptr)
	{
		if (nodes[0] != nullptr) {
			int index = getIndex(*pRect);

			if (index != -1) {
				nodes[index]->insert(pRect);

				return;
			}
		}
	}
	
	rectObjects.push_back(pRect);

	if (rectObjects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
		if (nodes == nullptr) {
			split(); 
		}//*/
		

		int i = 0;
		while (i < rectObjects.size()) {
			int index = getIndex(*rectObjects.at(i));
			if (index != -1) {
				nodes[index]->insert(rectObjects[i]);
				rectObjects.erase(rectObjects.begin() + i);
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
/*list<Rect*>* Quadtree::retrieve(list<Rect*> *returnObjects, Rect* pRect)
{
	int index = getIndex(*pRect);

	if (nodes != nullptr)
	{
		if (index != -1 && nodes[0] != nullptr) {
			nodes[index]->retrieve(returnObjects, pRect);
		}
	}
	

	//returnObjects.addAll(objects);
	for ( deque<Rect*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		returnObjects->push_back(*it);
	}
	return returnObjects;
}//*/
list<RectObject*>* Quadtree::retrieve(list<RectObject*> *returnObjects, RectObject* pRect)
{
	int index = getIndex(*pRect);

	if (nodes != nullptr)
	{
		if (index != -1 && nodes[0] != nullptr) {
			nodes[index]->retrieve(returnObjects, pRect);
		}
	}


	//returnObjects.addAll(objects);
	for ( deque<RectObject*>::iterator it = rectObjects.begin(); it != rectObjects.end(); ++it)
	{
		returnObjects->push_back(*it);
	}
	return returnObjects;
}
void Quadtree::draw(bool DRAW_CONTAINED_ITEM_ID)
{
	drawRectBounds(bounds, red);

	if (rectObjects.size() > 0)//(objects.size() > 0)
	{
		glColor3f(red.x, red.y, red.z);
		for (int i = 0; i < rectObjects.size(); i++)//objects.size();
		{
			glm::vec3 v1 = calcRelativePoints2D(bounds.sx,bounds.sy,screenW,screenH);
			glRasterPos2f(v1.x, v1.y - 0.07f - (i * 0.07f));
			glutBitmapString(GLUT_BITMAP_HELVETICA_18, rectObjects.at(i)->id_c);//objects.at(i)->id_c
			
		}
		
	}
	
	if (nodes != nullptr)
	{
		for (int i = 0; i < numOfNodes; i++)
		{
			if (nodes[i] != nullptr)
			{
				nodes[i]->draw(true);
			}
		}
	}
}
void Quadtree::draw()
{
	drawRectBounds(bounds, red);
	if (nodes != nullptr)
	{
		for (int i = 0; i < numOfNodes; i++)
		{
			if (nodes[i] != nullptr)
			{
				nodes[i]->draw();
			}
		}
	}
}
void Quadtree::drawRectBounds(Rect r, glm::vec3 color)
{
	glColor3f(color.x, color.y, color.z);
	glBegin(GL_LINE_LOOP);

	//glm::vec3 v1(r.sx, r.sy, 0);
	glm::vec3 v1 = calcRelativePoints2D(r.sx,r.sy,screenW,screenH);
	//glm::vec3 v2(r.sx, r.ey, 0);
	glm::vec3 v2 = calcRelativePoints2D(r.sx,r.ey,screenW,screenH);
	//glm::vec3 v3(r.ex, r.ey, 0);
	glm::vec3 v3 = calcRelativePoints2D(r.ex,r.ey,screenW,screenH);
	//glm::vec3 v4(r.ex, r.sy, 0);
	glm::vec3 v4 = calcRelativePoints2D(r.ex,r.sy,screenW,screenH);

	glVertex3f(v1.x,v1.y,v1.z);
	glVertex3f(v2.x,v2.y,v2.z);
	glVertex3f(v3.x,v3.y,v3.z);
	glVertex3f(v4.x,v4.y,v4.z);

	glEnd();

}
glm::vec3 Quadtree::calcRelativePoints2D(int x, int y, int screenWidth, int screenHeight)
{
	float w = screenWidth / 2;
	float h = screenHeight / 2;

	float newX = (x - w) / w;
	float newY = (h - y) / h;

	glm::vec3 newCord(newX, newY, 0.0f);
	return newCord;
}
