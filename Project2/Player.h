#pragma once
#include "GameStructs.h"
#include "Sprites.h"
#include "Objects.h"
#include "Bullets.h"
#include "Walls.h"

class Enemies;

class Player : private Objects
{
private:
	std::vector<Walls*>::iterator walls;
	std::vector<Enemies*>::iterator enemies;
	std::vector<Bullets*> bullets;
	float x, y, v = 64, vec[2];
	double lastShot = 0;
	POINT* posit;
	int countOfBullets = 10;
	int lives = 3;
	Sprites* sprite;
	Graphics* gfx;
	void Move(KeyDirections key, double timeDelta);
	void SetInTheBorders();
	Bullets* Shoot(double timeTotal);
	POINT* mPoint = new POINT;
	void Update(double timeDelta, double timeTotal);
	void Reload(double timeTotal);
public:
	POINT* GetCoordinate();
	void Init(std::vector<Walls*>::iterator walls, std::vector<Enemies*>::iterator enemies);
	Player(float x, float y, Graphics* gfx);
	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mPoint) override;
	void Render() override;
	bool Death();
	/*bool Touch() override;
	bool Touched() override;*/
};

