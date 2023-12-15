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
	virtual void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mpoint) = 0;
	virtual void Render() = 0;
	/*virtual bool Touch() = 0;
	virtual bool Touched() = 0;*/
	virtual void Update(double timeDelta, double timeTotal) = 0;
};

