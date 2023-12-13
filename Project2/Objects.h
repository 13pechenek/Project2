#pragma once
#include <cmath>
#include <vector>
#include"Sprites.h"
#include "GameStructs.h"

class Objects
{
private:
	static int counter;

public:	
	Graphics* gfx;
	virtual void Update(double timeDelta, KeyDirections key, POINT mpoint) = 0;
	virtual void Render() = 0;
	/*virtual bool Touch() = 0;
	virtual bool Touched() = 0;*/
};

