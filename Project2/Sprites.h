#pragma once

#include <wincodec.h>
#include "Graphics.h"

class Sprites
{
	Graphics* gfx;
	ID2D1Bitmap* bmp;
public:
	Sprites(const wchar_t* filename, Graphics* gfx);
	~Sprites();
	void Draw();
	void DrawAtPlace(float x, float y);
};

