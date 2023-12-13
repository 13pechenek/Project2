#pragma once
#include <cmath>
#include "Objects.h"
#include "GameController.h"
#include "Player.h"
#include "Bullets.h"

class Enemies : Objects
{

private:
	Player* player;
	std::vector<Bullets*> bullets;
	static int counter;
	float x, y;
	float v = 30;
	float distance_to_Player;
	int count_of_bullets = 20;
	Sprites* sprite = new Sprites(L"test.png", gfxx);
	bool decide_to_move()
	{
		if (distance_to_Player < 200) return true; else return false;
	}
	bool able_to_see()
	{
		return true;
	}

	void move(double timeDelta)
	{
		if (!distance_to_Player) return;
		CalcDistance();
		float cos = sqrt(pow((player->GetCoordinate().x - this->x), 2)) / distance_to_Player;
		float sin = sqrt(pow((player->GetCoordinate().y - this->y), 2)) / distance_to_Player;
		this->x += v * cos * timeDelta;
		this->y += v * sin * timeDelta;
	}

	

	Bullets* Shoot()
	{
		return new Bullets(x, y, player->GetCoordinate());
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

	



	void Update(double timeDelta) override
	{
		for (Bullets* n : bullets) n->Update(timeDelta);
		if (able_to_see())
		{
			if (decide_to_move())
			{
				move(timeDelta);
			}
			else 
			{
				bullets.push_back(Shoot());

			}
		}
	}
	
	void Render() override
	{
		sprite->DrawAtPlace(x, y);
		for (Bullets* n : bullets) n->Render();
	}
	/*bool Touch() override;
	bool Touched() override;*/
};

