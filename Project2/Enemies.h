#pragma once
#include <cmath>
#include "Objects.h"
#include "GameController.h"
#include "Player.h"
#include "Bullets.h"

class Enemies : Objects
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
	float v = 30;
	float distance_to_Player;
	float lastShot = 0;
	bool decide_to_move();
	bool able_to_see();
	void move(double timeDelta);
	void Reload(double timeTotal);
	void CalcDistance();
	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mpoint) override;
	Bullets* Shoot(double timeTotal);


public:
	ID2D1RectangleGeometry* geometry;
	void Update(double timeDelta, double timeTotal) override;
	void Render() override;
	bool Overlapped(Walls* wall, ID2D1TransformedGeometry* ray);
	bool Damaged();
	Enemies(float x, float y, Player* player, SinglyLinkedList<Walls*>* walls, Graphics* gfx);
	~Enemies();

};


	
	

