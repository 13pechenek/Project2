#pragma once
#include "GameStructs.h"
#include "Sprites.h"
#include "Objects.h"

class Player : private Objects
{
private:
	static int counter;
	float x, y, v = 20, vec[2];
	int countOfBullets = 10;
	int lives = 3;
	Sprites* sprite;
	void Move(KeyDirections key, double timeDelta);
	void SetInTheBorders();
	void Shoot();
public:
	Player(float x, float y, Graphics* gfx);
	void Update(double timeDelta, KeyDirections key) override;
	void Render() override;
	bool Death();
	/*bool Touch() override;
	bool Touched() override;*/
};

