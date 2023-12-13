#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::Loading;
FPSControl* GameController::Timer;




void GameController::LoadInitialLevel(GameLevel* level) 
{
	Loading = true;
	currentLevel = level;
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
	Timer = new FPSControl();
}
void GameController::SubInit() 
{
	Timer->SetFreq();
	Timer->Reset();
}
void GameController::TimerRefresh()
{
	Timer->Reset();
}


void GameController::Update(KeyDirections key, POINT Mpostion)
{
	if (Loading) return;
	Timer->Update();
	currentLevel->Update(Timer->GetTimeTotal(), Timer->GetTimeDelta(), key, Mpostion);
}