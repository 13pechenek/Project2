#pragma once

#include <wincodec.h>
#include "Graphics.h"

class Sprites
{
	Sprites();
	Graphics* gfx;
	ID2D1Bitmap* bmp;

public:
	ID2D1RectangleGeometry* geometry;
	Sprites(const wchar_t* filename, Graphics* gfx);
	~Sprites();
	void Draw();
	void DrawAtPlace(float left, float top);
	void DrawAtPlace(float left, float top, float right, float bottom);
};

