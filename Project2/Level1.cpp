#include "Level1.h"
#include "GameController.h"


float x1 = rand() % 1920, x2 = rand() % 1920, x3 = rand() % 1920, x4 = rand() % 1920, x5 = rand() % 1920, x6 = rand() % 1920, x7 = rand() % 1920, x8 = rand() % 1920, x9 = rand() % 1920, x10 = rand() % 1920, x11 = rand() % 1920, x12 = rand() % 1920, x13 = rand() % 1920, x14 = rand() % 1920, x15 = rand() % 1920, x16 = rand() % 1920;
float y100 = rand() % 1080, y2 = rand() % 1080, y3 = rand() % 1080, y4 = rand() % 1080, y5 = rand() % 1080, y6 = rand() % 1080, y7 = rand() % 1080, y8 = rand() % 1080, y9 = rand() % 1080, y10 = rand() % 1080, y11 = rand() % 1080, y12 = rand() % 1080, y13 = rand() % 1080, y14 = rand() % 1080, y15 = rand() % 1080, y16 = rand() % 1080;

void Level1::Load()
{

	player = new Player(0, 0, gfx);
	cat = new Sprites(L"cat.png", gfx);
}

void Level1::Unload()
{
	delete cat;
}
void Level1::Render() 
{
	gfx->ClearScreen(0.7f, 0.7f, 0.2f);
	player->Render();
	cat->DrawAtPlace(x1,y100,x2,y2);
	cat->DrawAtPlace(x3,y3,x4,y4);
	cat->DrawAtPlace(x5, y5, x6, y6);
	cat->DrawAtPlace(x7, y7, x8, y8);
	cat->DrawAtPlace(x9, y9, x10, y10);
	cat->DrawAtPlace(x11, y11, x12, y12);
	cat->DrawAtPlace(x13, y13, x14, y14);
	cat->DrawAtPlace(x15, y15, x16, y16);
}
void Level1::Update(double timeTotal, double timeDelta)
{
	return;
}
void Level1::Update(double timeTotal, double timeDelta, KeyDirections key, POINT* Mpostion)
{
	player->Update(timeDelta, timeTotal, key, Mpostion);
}

