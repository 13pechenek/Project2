#pragma once
#include"Sprites.h"
#include "GameStructs.h"
class Objects
{
private:
	static int counter;
public:
	virtual void Update(double timeDelta, KeyDirections key) = 0;
	virtual void Render() = 0;
	virtual bool Touch() = 0;
	virtual bool Touched() = 0;
	
};

