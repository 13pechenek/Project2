/*#pragma once
#include "Objects.h"

class Walls : Objects
{
private:
	float x, y;
	float len, width;
	static int counter;
	POINT posit;
	Sprites* sprite;

public:
	Walls(float x, float y, float len, float width, Graphics* gfx)
	{
		this->x = x;
		this->y = y;
		this->len = len;
		this->width = width;
		sprite =  new  Sprites(L"wall.png", gfx);
	}

	void Render() override
	{
		sprite->DrawAtPlace(x, y);
	}


};*/

