#include "Level1.h"
#include "GameController.h"


float x1 = rand() % 1920, x2 = rand() % 1920, x3 = rand() % 1920, x4 = rand() % 1920, x5 = rand() % 1920, x6 = rand() % 1920, x7 = rand() % 1920, x8 = rand() % 1920, x9 = rand() % 1920, x10 = rand() % 1920, x11 = rand() % 1920, x12 = rand() % 1920, x13 = rand() % 1920, x14 = rand() % 1920, x15 = rand() % 1920, x16 = rand() % 1920;
float y100 = rand() % 1080, y2 = rand() % 1080, y3 = rand() % 1080, y4 = rand() % 1080, y5 = rand() % 1080, y6 = rand() % 1080, y7 = rand() % 1080, y8 = rand() % 1080, y9 = rand() % 1080, y10 = rand() % 1080, y11 = rand() % 1080, y12 = rand() % 1080, y13 = rand() % 1080, y14 = rand() % 1080, y15 = rand() % 1080, y16 = rand() % 1080;

void Level1::Load()
{	
	w.push_back(new Walls(100, 100, 150, 300, gfx));
	w.push_back(nullptr);
	walls = w.begin();

	player = new Player(0, 0, gfx);
	e.push_back(new Enemies(200, 200, player, walls, gfx));
	e.push_back(nullptr);

	enemies = e.begin();
	player->Init(walls, enemies);
	



}

void Level1::Unload()
{
	delete cat;
}
void Level1::Render() 
{
	gfx->ClearScreen(0.7f, 0.7f, 0.2f);
	if(!player->Death()) player->Render();
}
void Level1::Update(double timeTotal, double timeDelta)
{
	return;
}
void Level1::Update(double timeTotal, double timeDelta, KeyDirections key, POINT* Mpostion)
{
	player->Update(timeDelta, timeTotal, key, Mpostion);
}

