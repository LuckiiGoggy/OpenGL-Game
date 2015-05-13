#include "Overlay2D.h"
#include "windows.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "SOIL.h"

Overlay2D::Overlay2D()
{
}


Overlay2D::~Overlay2D()
{
}

void Overlay2D::prepare2D(int left, int top, int right, int bottom)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0, 0, bottom, top, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Overlay2D::Render() 
{
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glEnable(GL_BLEND);
	//Render Your Images Here---------------------------------------------------------------------------

	

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0);

		glVertex2f(-10.0, -10.0);
		glVertex2f(10.0, -10.0);
		glVertex2f(10.0, 10.0);
		glVertex2f(-10.0, 10.0);
	glEnd();










	//Stop rendering images here--------------------------------------------------------------------------
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	unprepare2D();
}

void Overlay2D::unprepare2D()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
