#pragma once

#include "GameLevel.h"
#include "FPSControl.h"




class GameController
{
	GameController();
	static GameLevel* currentLevel;
	static FPSControl* Timer;
public:
	static bool Loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);
	static void Update();
	static void Update(KeyDirections key, POINT* MPostion);
	static void Render();
	static void UnloadCurrentLevel();
};