#pragma once
#include <cmath>

#include "GameController.h"
#include "Player.h"
#include "Bullets.h"

class Enemies
{

private:
	Enemies();
	ID2D1RectangleGeometry* rectangle;
	ID2D1TransformedGeometry* ray;
	Sprites* sprite;
	Graphics* gfx;
	Player* player;
	SinglyLinkedList<Walls*>* walls;
	SinglyLinkedList<Bullets*> bullets;
	int countOfBullets = 10;
	int lives = 1;
	float x, y;
	float v = 120;
	float distance_to_Player;
	float lastShot = 0;
	bool decide_to_move();
	bool able_to_see();
	void move(double timeDelta);
	void Reload(double timeTotal);
	void CalcDistance();
	Bullets* Shoot(double timeTotal);
public:
	ID2D1RectangleGeometry* geometry;
	void Update(double timeDelta, double timeTotal);
	void Render();
	bool Overlapped(Walls* wall, ID2D1TransformedGeometry* ray);
	bool Damaged();
	Enemies(float x, float y, Player* player, SinglyLinkedList<Walls*>* walls, Graphics* gfx);
	~Enemies();

};


	
	

