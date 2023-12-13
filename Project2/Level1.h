#pragma once

#include "GameLevel.h"
#include "Player.h"


class Level1 : public GameLevel
{
	double vec[2]{ 0, 0 };
	Sprites* sprites;
	Player* player;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void Update(double timeTotal, double timeDelta, KeyDirections key) override;
};