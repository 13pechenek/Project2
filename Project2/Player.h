#pragma once
#include "GameStructs.h"
#include "Sprites.h"
#include "Objects.h"

class Player : private Objects
{
private:
	float v = 20;
	static int counter;
	double vec[2];
	float x, y;
	bool able_to_move;
	int count_of_bullets = 10;
	int Lives = 3;
	Sprites* sprite;
	void move(KeyDirections key, double timeDelta)
	{

		vec[0] = 0;
		vec[1] = 0;
		if (key.up && !key.left && !key.right && !key.down) {
			vec[1] = -1;
			vec[0] = 0;
		}
		if (key.up && key.left && !key.right && !key.down) {
			vec[1] = -0.7071;
			vec[0] = -0.7071;
		}
		if (key.up && !key.left && key.right && !key.down) {
			vec[1] = -0.7071;
			vec[0] = 0.7071;
		}
		if (key.up && !key.left && !key.right && key.down) {
			vec[1] = 0;
			vec[0] = 0;
		}
		if (!key.up && !key.left && !key.right && key.down) {
			vec[1] = 1;
			vec[0] = 0;
		}
		if (!key.up && key.left && !key.right && key.down) {
			vec[1] = 0.7071;
			vec[0] = -0.7071;
		}
		if (!key.up && !key.left && key.right && key.down) {
			vec[1] = 0.7071;
			vec[0] = 0.7071;
		}
		if (!key.up && key.left && !key.right && !key.down) {
			vec[0] = -1;
			vec[1] = 0;
		}
		if (!key.up && !key.left && key.right && !key.down) {
			vec[0] = 1;
			vec[1] = 0;
		}
		if (!key.up && key.left && key.right && !key.down) {
			vec[0] = 0;
			vec[1] = 0;
		}



		y += v * timeDelta * vec[1];
		x += v * timeDelta * vec[0];

		if (y > 500)
		{
			y = 500;
		}
		else if (y < 0)
		{
			y = 0;
		}
		if (x > 700)
		{
			x = 700;
		}
		else if (x < 0)
		{
			x = 0;
		}
	}

	void shoot()
	{
		return; //say gex
	}


public:

	Player(float x, float y, Graphics* gfx)   // Player* player 
	{
		sprite = new Sprites(L"test.png", gfx);
		this->x = x; 
		this->y = y;
	}


	bool Death()
	{
		return Lives == 0;
	}




	void Update(double timeDelta, KeyDirections key) override
	{
		move(key, timeDelta);
		return;  
	}
	
	void Render() override
	{
		(*sprite).DrawAtPlace(x, y);
	}
	/*bool Touch() override;
	bool Touched() override;*/
};

