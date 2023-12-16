#pragma once
#include "Objects.h"
#include "Sprites.h"
#include "Walls.h"


class Player;
class Enemies;

class Bullets : private Objects
{
private:
	Bullets();
	float x, y, v = 100, Sinus = 0, Cosin = 0, distanceToPoint;
	POINT* aimPos;
	Graphics* gfx;
	SinglyLinkedList<Enemies*>* enemies;
	SinglyLinkedList<Walls*>* walls;
	Player* player;
	ID2D1EllipseGeometry* geometry;
	void move(double timeDelta);
	void ResetDistance();
	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mpoint) override;

public:
	Bullets(float x, float y, POINT* aimPos, Graphics* gfx, SinglyLinkedList<Enemies*>* enemies, SinglyLinkedList<Walls*>* walls, Player* player);
	void Update(double timeDelta, double timeTotal) override;
	void Render() override;
	bool EnemyTouched();
	bool PlayerTouched();
	bool WallTouched();
	~Bullets();
};

