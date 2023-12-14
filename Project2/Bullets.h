#pragma once
#include "Objects.h"
#include "Sprites.h"


class Bullets : private Objects
{
private:
	float x, y, v=100, Sinus, Cosin, distanceToPoint;
	POINT* aimPos;
	Graphics* gfx;
	void move(double timeDelta);
	void ResetDistance();
	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mpoint) override;
public:
	Bullets(float x, float y, POINT* aimPos, Graphics* gfx);
	void Update(double timeDelta) override;
	void Render() override;
};

