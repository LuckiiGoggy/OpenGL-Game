
#include "Rect.h"

Rect::Rect()
{
	sx = 0;
	sy = 0;
	ex = 0;
	ey = 0;
}
Rect::Rect(int xs, int ys, int xe, int ye)
{
	sx = xs;
	sy = ys;
	ex = xe;
	ey = ye;
}

int Rect::getWidth()
{
	int w = (ex - sx);
	return abs(w);
}
int Rect::getHeight()
{
	int h = (ey - sy);
	return abs(h);
}