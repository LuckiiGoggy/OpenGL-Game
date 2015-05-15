#ifndef OVERLAY_H
#define OVERLAY_H
#pragma once
#include "openGL.h"
#include "TextControl.h"

class Overlay2D
{
public:
	Overlay2D();
	~Overlay2D();
	void prepare2D(int, int, int, int);
	void Render();
	void unprepare2D();

	CGameFont* m_pFont;
	CTextControl* m_pNewGameText;
};

#endif