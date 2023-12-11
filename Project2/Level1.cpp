#include "Level1.h"
#include "GameController.h"



void Level1::Load()
{
	y = 0;
	x = 0;
	v_x = 1;
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
void Level1::Update() 
{
	v_y += a_y;
	y += v_y;
	x += v_x;
	if (y > 600)
	{
		y = 600;
		v_y = -v_y;
	}
	else if (y < 0)
	{
		y = 0;
		v_y = -v_y;
	}
	if (x > 800)
	{
		x = 800;
		v_x = -v_x;
	}
	else if (x < 0)
	{
		x = 0;
		v_x = -v_x;
	}
}