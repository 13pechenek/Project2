#pragma once

#include "GameLevel.h"


class Level1 : public GameLevel
{
	float y;
	float x;
	float v_x;
	float v_y;
	float a_y = 10;
	float v_x1;
	float v_y1;
	float a_y1;
	Sprites* sprites;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;

};