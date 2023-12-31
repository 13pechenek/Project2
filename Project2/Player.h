#pragma once
#include "GameStructs.h"
#include "Sprites.h"




class Enemies;
class Walls;
class Bullets;

class Player
{
private:
	Player();
	SinglyLinkedList<Enemies*>* enemies;
	SinglyLinkedList<Walls*>* walls;
	SinglyLinkedList<Bullets*> bullets;
	float x, y, v = 120, vec[2];
	double lastShot = 0;
	POINT* posit;
	int countOfBullets = 10;
	int lives = 3;
	Sprites* sprite;
	Graphics* gfx;
	void Move(KeyDirections key, double timeDelta);
	void SetInTheBorders(double timeDelta);
	Bullets* Shoot(double timeTotal);
	POINT* mPoint = new POINT;
	void Update(double timeDelta, double timeTotal);
	void Reload(double timeTotal);
public:
	ID2D1RectangleGeometry* geometry;
	POINT* GetCoordinate();
	void Init(SinglyLinkedList<Walls*>* walls, SinglyLinkedList<Enemies*>* enemies);
	Player(float x, float y, Graphics* gfx);
	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mPoint);
	void Render();
	bool Death();
	ID2D1RectangleGeometry* GetGeometry() { return geometry; }
	void Damaged();
	~Player();

};