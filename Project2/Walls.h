#pragma once
#include "Objects.h"

class Walls : private Objects
{
private:
	float left, top;
	float right, bottom;
	static int counter;
	POINT posit;
	Sprites* sprite;
	void Update(double timeDelta) 
	{

	}
	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mPoint)
	{

	}
public:
	Walls(float left, float top, float right, float bottom, Graphics* gfx)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		sprite =  new  Sprites(L"Wall.png", gfx);
	}

	void Render() override
	{
		sprite->DrawAtPlace(left, top, right, bottom);
	}


};

