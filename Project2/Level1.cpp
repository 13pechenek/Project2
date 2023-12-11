#include "Level1.h"
#include "GameController.h"



void Level1::Load()
{
	y = 0;
	x = 0;
	v_x = 10;
	v_y = 0;
	sprites = new Sprites(L"test.png", gfx);
}

void Level1::Unload()
{
	delete sprites;
}
void Level1::Render() 
{
	gfx->ClearScreen(0.7f, 0.7f, 0.2f);
	gfx->DrawRect(x, y, 100, 100, 0, 0, 1);

	sprites->DrawAtPlace(x,y);
}
void Level1::Update(double timeTotal, double timeDelta)
{
	v_y += a_y * timeDelta*10;
	y += v_y;
	x += v_x * timeDelta*10;
	if (y > 500)
	{
		y = 500;
		v_y = -v_y;
	}
	else if (y < 0)
	{
		y = 0;
		v_y = -v_y;
	}
	if (x > 700)
	{
		x = 700;
		v_x = -v_x;
	}
	else if (x < 0)
	{
		x = 0;
		v_x = -v_x;
	}
}