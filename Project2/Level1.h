#pragma once

#include "GameLevel.h"


class Level1 : public GameLevel
{
	float y;
	float x;
	float v_x;
	float v_y;
	const float a_y = 10;
	Sprites* sprites;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
};