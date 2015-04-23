#ifndef RECT_H
#define RECT_H

#include "Math.h"

class Rect
{
public:

	Rect();
	Rect(int sx, int sy, int ex, int ey);

	int getWidth();
	int getHeight();

	int sx;
	int sy;
	int ex;
	int ey;
};
#endif
