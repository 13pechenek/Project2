#include "Level1.h"
#include "GameController.h"
#include "InputOutput.h"



void Level1::Load()
{	
	InputOutput::Init();
	InputOutput::Input(gfx,&w,&e,&player);
	InputOutput::Distruct();
	player->Init(&w, &e);
}

void Level1::Unload()
{
	delete player;
}
void Level1::Render() 
{
	gfx->ClearScreen(0.7f, 0.7f, 0.2f);
	backgroung->Draw();
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

