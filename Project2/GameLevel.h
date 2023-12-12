#pragma once
#include "Graphics.h"
#include "Sprites.h"
#include "GameStructs.h"


class GameLevel
{
protected:
	static Graphics* gfx;
public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update(double timeTotal, double timeDelta) = 0;
	virtual void Update(double timeTotal, double timeDelta, KeyDirections key) = 0;
};

