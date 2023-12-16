#pragma once


class Walls
{
private:
	Walls();
	POINT posit;
	Sprites* sprite;
	Graphics* gfx;
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

	void Render()
	{
		sprite->DrawAtPlace(left, top, right, bottom);
	}


};

