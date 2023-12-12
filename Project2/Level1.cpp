#include "Level1.h"
#include "GameController.h"



void Level1::Load()
{
	y = 0;
	x = 0;
	v = 80;
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
	return;
}
void Level1::Update(double timeTotal, double timeDelta, KeyDirections key)
{

	vec[0] = 0;
	vec[1] = 0;
	if (key.up && !key.left && !key.right && !key.down) {
		vec[1] = -1;
		vec[0] = 0;
	}
	if (key.up && key.left && !key.right && !key.down) {
		vec[1] = -0.7071;
		vec[0] = -0.7071;
	}
	if (key.up && !key.left && key.right && !key.down) {
		vec[1] = -0.7071;
		vec[0] = 0.7071;
	}
	if (key.up && !key.left && !key.right && key.down) {
		vec[1] = 0;
		vec[0] = 0;
	}
	if (!key.up && !key.left && !key.right && key.down) {
		vec[1] = 1;
		vec[0] = 0;
	}
	if (!key.up && key.left && !key.right && key.down) {
		vec[1] = 0.7071;
		vec[0] = -0.7071;
	}
	if (!key.up && !key.left && key.right && key.down) {
		vec[1] = 0.7071;
		vec[0] = 0.7071;
	}
	if (!key.up && key.left && !key.right && !key.down) {
		vec[0] = -1;
		vec[1] = 0;
	}
	if (!key.up && !key.left && key.right && !key.down) {
		vec[0] = 1;
		vec[1] = 0;
	}
	if (!key.up && key.left && key.right && !key.down) {
		vec[0] = 0;
		vec[1] = 0;
	}

	

	y += v * timeDelta * vec[1];
	x += v * timeDelta * vec[0];

	if (y > 500)
	{
		y = 500;
	}
	else if (y < 0)
	{
		y = 0;
	}
	if (x > 700)
	{
		x = 700;
	}
	else if (x < 0)
	{
		x = 0;
	}
}

