#include "Overlay2D.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "Dependencies\soil\src\SOIL.h"
#include <string>

Overlay2D::Overlay2D()
{
	health = 3;
	ammo = 3;
	score = 0;
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
	
	glColor3f(0.576, 0.094, 0.816);
	glRasterPos2f(-1.0, 0.95);
	std::string output;
	output = "Health: ";
	output += std::to_string(health);
	int len, i;
	len = output.size();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, output[i]);
	}

	glColor3f(0.576, 0.094, 0.816);
	glRasterPos2f(0.85, -1.0);
	output = "Ammo: ";
	output += std::to_string(ammo);
	output += "/3";
	len = output.size();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, output[i]);
	}

	glColor3f(0.576, 0.094, 0.816);
	glRasterPos2f(-0.05, 0.95);
	output = "Score: ";
	output += std::to_string(score);
	len = output.size();
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, output[i]);
	}
	


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

void Overlay2D::increaseAmmo() { ammo++; }
void Overlay2D::decreaseAmmo() { ammo--; }
void Overlay2D::increaseHP() { health++; }
void Overlay2D::decreaseHP() { health--; }
void Overlay2D::increaseScore() { score++; }
void Overlay2D::decreaseScore() { score--; }
void Overlay2D::setAmmo(int i) { ammo = i; }
void Overlay2D::setHP(int i) { health = i; }
void Overlay2D::setScore(int i) { score = i; }
