#pragma once
#include <cmath>
#include "Objects.h"
#include "GameController.h"
#include "Player.h"

class Enemies : Objects
{

private:

	Player* player;
	static int counter;
	float x, y;
	float v = 30;
	float distance_to_Player;
	int count_of_bullets = 20;
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



	void move(double timeDelta)
	{
		CalcDistance();
		float cos = sqrt(pow((player->GetCoordinate().x - this->x), 2)) / distance_to_Player;
		float sin = sqrt(pow((player->GetCoordinate().y - this->y), 2)) / distance_to_Player;
		if (able_to_see())
		{
			if (distance_to_Player < 200)
			{
				this->x += v * cos * timeDelta;
				this->y += v * sin * timeDelta;
			}
		}



	}

	
	
	void shoot()
	{
		return; //say gex
	}


	void CalcDistance()
	{
		this->distance_to_Player = sqrt(pow((player->GetCoordinate().x - x), 2) + pow((player->GetCoordinate().y - y), 2));
		return;
	}




public:
	Graphics* gfxx;
	Enemies(float x, float y, Player* player) 
	{
		this->x = x; 
		this->y = y;
		this->player = player;
	}
    void Init(Graphics* gfix);

	



	void Update(double timeDelta, KeyDirections key) override
	{
		if (able_to_see())
		{
			if (decide_to_move())
			{
				move(timeDelta);
				shoot();
			}

			else if (decide_to_shoot())
			{
				move(timeDelta);
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

