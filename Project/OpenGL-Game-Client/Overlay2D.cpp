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
	//glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glEnable(GL_BLEND);
	//Render Your Images Here---------------------------------------------------------------------------

	GLuint tex_2d = SOIL_load_OGL_texture
		(
		"../Assets/Images/heart.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_2d);

	for (int i = 1; i <= health; i++)
	{
		glBegin(GL_QUADS);
		float offset = (3 - i)*0.05;
		glTexCoord2f(0, 0); glVertex2f(-0.9 - offset, 1.0);;
		glTexCoord2f(0, 1); glVertex2f(-0.85 - offset, 1.0);
		glTexCoord2f(1, 1); glVertex2f(-0.85 - offset, 0.95);
		glTexCoord2f(1, 0); glVertex2f(-0.9 - offset, 0.95);
		glEnd();
	}
	GLuint tex2_2d = SOIL_load_OGL_texture
		(
		"../Assets/Images/spear.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex2_2d);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(0.95, 1.0);;
		glTexCoord2f(0, 1); glVertex2f(0.9, 1.0);
		glTexCoord2f(1, 1); glVertex2f(0.9, 0.95);
		glTexCoord2f(1, 0); glVertex2f(0.95, 0.95);
	glEnd();

	glDisable(GL_BLEND);

	std::string output;
	int len, i;
	glColor3f(0.576, 0.094, 0.816);
	glRasterPos2f(0.94, 0.95);
	output = ": ";
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

void Overlay2D::increaseAmmo() {
	if (ammo <= 3)
		ammo++;
}

void Overlay2D::decreaseAmmo() {
	if (ammo > 0)
		ammo--;
}

void Overlay2D::increaseHP() {
	if (health <= 3)
		health++;
}

void Overlay2D::decreaseHP() {
	if (health > 0)
		health--;
}

void Overlay2D::increaseScore() { score++; }
void Overlay2D::decreaseScore() { score--; }
void Overlay2D::setAmmo(int i) { ammo = i; }
void Overlay2D::setHP(int i) { health = i; }
void Overlay2D::setScore(int i) { score = i; }
