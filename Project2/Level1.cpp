#include "Level1.h"
#include "GameController.h"


void Level1::Load()
{
	y = 0;
	x = 0;
	v_x = 1;
	v_y = 0;
}

void Level1::Unload()
{

}
void Level1::Render(Graphics* gfx) 
{
	gfx->ClearScreen(0.7f, 0.7f, 0.2f);
	gfx->DrawCircle(x, y, 50.0, 0, 0, 1, 1);
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