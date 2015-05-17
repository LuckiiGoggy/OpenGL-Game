#pragma once
#include "BoundingBox.h"
class BoundingBoxLibrary
{
public:
	static void InitBoxes();


	static BoundingBox *NewPlayer(void);
	static BoundingBox *NewWall(void);
	static BoundingBox *NewProjectile(void);

protected:
	static BoundingBox *playerBox;
	static BoundingBox *wallBox;
	static BoundingBox *spearBox;

};

