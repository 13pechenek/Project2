#include "Bullets.h"


Bullets::Bullets(float x, float y, POINT aimPos)
{
	if (!distanceToPoint) return;
	this->x = x;
	this->y = y;
	this->aimPos = aimPos;
	ResetDistance();
	cos = sqrt(pow((aimPos.x - this->x), 2)) / distanceToPoint;
	sin = sqrt(pow((aimPos.y - this->y), 2)) / distanceToPoint;
}

void Bullets::Update(double timeDelta, KeyDirections key, POINT mPoint)
{
	move(timeDelta);
}

void Bullets::move(double timeDelta)
{
	if (!distanceToPoint) return;
	this->x += v * cos * timeDelta;
	this->y += v * sin * timeDelta;
}

void Bullets::ResetDistance()
{
	distanceToPoint = sqrt(pow((aimPos.x - x), 2) + pow((aimPos.y - y), 2));
}

void Bullets::Render()
{
	gfx->DrawCircle(x, y, 2.5, 1, 0, 0, 1);
}