#pragma once
#include <cmath>
#include "Objects.h"
#include "GameController.h"

class Enemies : Objects
{

private:

	static int counter;
	float x, y;
	float distance_to_Player;
	bool able_to_move;
	int count_of_bullets = 20;
	bool see_Player = true;
	Sprites* sprite = new Sprites(L"test.png", gfxx);
	bool decide_to_move()
	{
		return true;
	}
	bool decide_to_shoot()
	{
		return false;
	}
	bool able_to_see()
	{
		return true;
	}
	void move()
	{
		return;
	}

	void shoot()
	{
		return; //say gex
	}


	void CalcDistance()
	{
		// this->distance_to_Player = sqrt(pow((player.x - x), 2) + pow((player.y - y), 2));
		return;
	}




public:
	Graphics* gfxx;
	Enemies(float x, float y)   // Player* player 
	{
		this->x = x; this->y = y;
		
	}
    void Init(Graphics* gfix);

	



	void Update(double timeDelta, KeyDirections key) override
	{
		if (this->able_to_see())
		{
			if (this->decide_to_move())
			{
				move();
				shoot();
			}

			else if (this->decide_to_shoot())
			{
				move();
				shoot();
			}
		}
	}
	void Render() override
	{
		sprite->DrawAtPlace(x, y);
	}
	/*bool Touch() override;
	bool Touched() override;*/
};

