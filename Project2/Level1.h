#pragma once

#include "GameLevel.h"



class Level1 : public GameLevel
{
	double vec[2]{ 0, 0 };
	float y;
	float x;
	float v;
	Sprites* sprites;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void Update(double timeTotal, double timeDelta, KeyDirections key) override;

};