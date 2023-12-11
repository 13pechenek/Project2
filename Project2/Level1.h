#pragma once

#include "GameLevel.h"


class Level1 : public GameLevel
{
	float y;
	float x;
	float v_x;
	float v_y;
	const float a_y = 1;
public:
	void Load() override;
	void Unload() override;
	void Render(Graphics* graphics) override;
	void Update() override;
};