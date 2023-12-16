#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::Loading;
FPSControl* GameController::Timer;




void GameController::LoadInitialLevel(GameLevel* level) 
{
	Loading = true;
	currentLevel = level;
	Timer = new FPSControl();
	currentLevel->Load();
	Loading = false;
}

void GameController::SwitchLevel(GameLevel* level)
{
	Loading = true;
	currentLevel->Unload();
	level->Load();
	delete currentLevel;
	currentLevel = level;
	Loading = false;
}

void GameController::Render()
{
	if (Loading) return;
	currentLevel->Render();

}

void GameController::Update()
{
	if (Loading) return;
	Timer->Update();
	currentLevel->Update(Timer->GetTimeTotal(), Timer->GetTimeDelta());
}
void GameController::Init()
{
	Loading = true;
	currentLevel = 0;

}


void GameController::Update(KeyDirections key, POINT* MPostion)
{
	if (Loading) return;
	Timer->Update();
	currentLevel->Update(Timer->GetTimeTotal(), Timer->GetTimeDelta(), key, MPostion);
}

void GameController::UnloadCurrentLevel()
{
	delete currentLevel;
	delete Timer;
}