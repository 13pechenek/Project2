#pragma once
#include "Objects.h"
#include "Sprites.h"
#include "Walls.h"


class Player;
class Enemies;

class Bullets : private Objects
{
private:
	float x, y, v=100, Sinus, Cosin, distanceToPoint;
	POINT* aimPos;
	Graphics* gfx;
	std::vector<Enemies*>::iterator enemies;
	std::vector<Walls*>::iterator walls;
	Player* player;
	ID2D1EllipseGeometry* geometry;
	void move(double timeDelta);
	void ResetDistance();
	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mpoint) override;

public:
	Bullets(float x, float y, POINT* aimPos, Graphics* gfx, std::vector<Enemies*>::iterator enemies, std::vector<Walls*>::iterator walls, Player* player);
	void Update(double timeDelta, double timeTotal) override;
	void Render() override;
	bool EnemyTouched();
	bool PlayerTouched();
	void WallTouched();
};

