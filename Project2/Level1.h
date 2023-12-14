#pragma once

#include "GameLevel.h"
#include "Player.h"
#include "Walls.h"


class Level1 : public GameLevel
{
private:
	double vec[2]{ 0, 0 };
	Sprites* cat;
	Walls* wall;
	Player* player;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void Update(double timeTotal, double timeDelta, KeyDirections key, POINT* Mpostion) override;
};