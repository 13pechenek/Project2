#include "Level1.h"
#include "GameController.h"




void Level1::Load()
{
	player = new Player(0, 0, gfx);
	sprites = new Sprites(L"test.png", gfx);
}

void Level1::Unload()
{
	delete sprites;
}
void Level1::Render() 
{
	gfx->ClearScreen(0.7f, 0.7f, 0.2f);
	player->Render();

}
void Level1::Update(double timeTotal, double timeDelta)
{
	return;
}
void Level1::Update(double timeTotal, double timeDelta, KeyDirections key, POINT Mpostion)
{
	player->Update(timeDelta, key);
}

