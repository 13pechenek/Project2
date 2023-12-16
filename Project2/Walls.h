#pragma once
#include "Objects.h"

class Walls : private Objects
{
private:
	Walls();
	POINT posit;
	Sprites* sprite;
	Graphics* gfx;
	void Update(double timeDelta, double timeTotal) 
	{

	}
	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mPoint)
	{

	}
public:
	float left, top;
	float right, bottom;
	ID2D1RectangleGeometry* geometry;
	Walls(float left, float top, float right, float bottom, Graphics* gfx)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		sprite =  new  Sprites(L"Wall.png", gfx);
		this->gfx = gfx;
		geometry = gfx->GetRectGeometry(left, top, right - left, bottom - top);
	}
	~Walls()
	{
		delete sprite;
		geometry->Release();
	}

	void Render() override
	{
		sprite->DrawAtPlace(left, top, right, bottom);
	}


};

