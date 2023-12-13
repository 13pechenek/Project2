#include "Bullets.h"


Bullets::Bullets(float x, float y, POINT* aimPos, Graphics* gfx)
{
	this->gfx = gfx;
	this->x = x;
	this->y = y;
	this->aimPos = aimPos;
	distanceToPoint = sqrt(pow((aimPos->x - x), 2) + pow((aimPos->y - y), 2));
	if (distanceToPoint == 0) return;
	Cosin = (aimPos->x - this->x) / distanceToPoint;
	Sinus = (aimPos->y - this->y) / distanceToPoint;
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
	this->x += v * Cosin * timeDelta;
	this->y += v * Sinus * timeDelta;
}

void Bullets::ResetDistance()
{
	distanceToPoint = sqrt(pow((aimPos->x - x), 2) + pow((aimPos->y - y), 2));
}

void Bullets::Render()
{
	gfx->DrawCircle(x, y, 2.5, 1, 0, 0, 1);
}