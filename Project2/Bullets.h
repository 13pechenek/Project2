#pragma once
#include "Objects.h"
#include "Sprites.h"

class Bullets : private Objects
{
private:
	float x, y, v, sin, cos, distanceToPoint;
	POINT aimPos;
	void move(double timeDelta);
	void ResetDistance();
	void Update(double timeDelta, KeyDirections key, POINT mpoint) override;
public:
	Bullets(float x, float y, POINT aimPos);
	void Update(double timeDelta) override;
	void Render() override;
};

