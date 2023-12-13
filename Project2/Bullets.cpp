#include "Bullets.h"


Bullets::Bullets(float x, float y, POINT* aimPos, Graphics* gfx)
{
	this->gfx = gfx;
	this->x = x;
	this->y = y;
	this->aimPos = aimPos;
	distanceToPoint = sqrt(pow((aimPos->x - x), 2) + pow((aimPos->y - y), 2));
	if (distanceToPoint == 0) return;
	cos = sqrt(pow((aimPos->x - this->x), 2)) / distanceToPoint;
	sin = sqrt(pow((aimPos->y - this->y), 2)) / distanceToPoint;
}

void Bullets::Update(double timeDelta)
{
	move(timeDelta);
}
void Bullets::Update(double timeDelta, KeyDirections key, POINT* mPosition)
{
	return;
}

void Bullets::move(double timeDelta)
{
	if (!distanceToPoint) return;
	this->x += v * cos * timeDelta;
	this->y += v * sin * timeDelta;
}

void Bullets::ResetDistance()
{
	distanceToPoint = sqrt(pow((aimPos->x - x), 2) + pow((aimPos->y - y), 2));
}

void Bullets::Render()
{
	gfx->DrawCircle(x, y, 2.5, 1, 0, 0, 1);
}