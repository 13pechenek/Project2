#pragma once

#include "Sprites.h"
#include "GameStructs.h"
#include "Walls.h"



class Player;
class Enemies;

class Bullets
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
	float red, green, blue;

public:
	Bullets(float x, float y, POINT* aimPos, Graphics* gfx, SinglyLinkedList<Enemies*>* enemies, SinglyLinkedList<Walls*>* walls, Player* player, float red, float green, float blue);
	void Update(double timeDelta);
	void Render();
	bool EnemyTouched();
	bool PlayerTouched();
	bool WallTouched();
	~Bullets();
};

