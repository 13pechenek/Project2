#pragma once

#include "GameLevel.h"
#include "Objects.h"
#include "Walls.h"
#include "Enemies.h"


class Level1 : public GameLevel
{
private:
	std::vector<Walls*>::iterator walls;
	std::vector<Enemies*>::iterator enemies;
	double vec[2]{ 0, 0 };
	Sprites* cat;
	Player* player;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void Update(double timeTotal, double timeDelta, KeyDirections key, POINT* Mpostion) override;
};