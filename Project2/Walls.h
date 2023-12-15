#pragma once
#include "Objects.h"

class Walls : private Objects
{
private:

	static int counter;
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
	ID2D1RectangleGeometry* rectangle;
	Walls(float left, float top, float right, float bottom, Graphics* gfx)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		sprite =  new  Sprites(L"Wall.png", gfx);
		this->gfx = gfx;
		rectangle = gfx->GetRectGeometry(left, top, right - left, bottom - top);
	}

	void Render() override
	{
		sprite->DrawAtPlace(left, top, right, bottom);
		//gfx->GetRenderTarget()->FillGeometry(rectangle, gfx->SetBrush());
	}


};

