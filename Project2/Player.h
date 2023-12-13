#pragma once
#include "GameStructs.h"
#include "Sprites.h"
#include "Objects.h"
#include "Bullets.h"

class Player : private Objects
{
private:
	static int counter;
	std::vector<Bullets*> bullets;
	float x, y, v = 64, vec[2];
	int countOfBullets = 10;
	int lives = 3;
	Sprites* sprite;
	void Move(KeyDirections key, double timeDelta);
	void SetInTheBorders();
	Bullets* Shoot();
	POINT mPoint;
public:
	POINT GetCoordinate();
	Player(float x, float y, Graphics* gfx);
	void Update(double timeDelta, KeyDirections key, POINT mPoint) override;
	void Render() override;
	bool Death();
	/*bool Touch() override;
	bool Touched() override;*/
};

