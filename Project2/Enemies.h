#pragma once
#include <cmath>
#include "Objects.h"
#include "GameController.h"
#include "Player.h"
#include "Bullets.h"

class Enemies : Objects
{

private:
	Sprites* sprite;
	Graphics* gfx;
	Player* player;
	std::vector<Walls*>::iterator walls;
	std::vector<Bullets*> bullets;
	int countOfBullets = 10;
	float x, y;
	float v = 30;
	float distance_to_Player;
	float lastShot = 0;
	int count_of_bullets = 20;
	bool decide_to_move()
	{
		if (distance_to_Player > 1000) return true; else return false;
	}
	bool able_to_see()
	{
		return true;
	}

	void move(double timeDelta)
	{

		if (!distance_to_Player) return;
		float cos = (player->GetCoordinate()->x - this->x) / distance_to_Player;
		float sin = (player->GetCoordinate()->y - this->y) / distance_to_Player;
		this->x += v * cos * timeDelta;
		this->y += v * sin * timeDelta;
	}

	void Reload(double timeTotal)
	{
		if (lastShot + 5 < timeTotal && !countOfBullets) countOfBullets = 10;
		else return;
	}

	Bullets* Shoot(double timeTotal)
	{
		Reload(timeTotal);
		if (lastShot + 1 < timeTotal && countOfBullets)
		{
			lastShot = timeTotal;
			countOfBullets--;
			return new Bullets(x + 25, y + 17, player->GetCoordinate(), gfx);
		}
		else return nullptr;
	}


	void CalcDistance()
	{
		this->distance_to_Player = sqrt(pow((player->GetCoordinate()->x - x), 2) + pow((player->GetCoordinate()->y - y), 2));
		return;
	}



	void Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mpoint) override
	{

	}
public:
	Enemies(float x, float y, Player* player, std::vector<Walls*>::iterator walls, Graphics* gfx)
	{
		this->gfx = gfx;
		this->x = x; 
		this->y = y;
		this->player = player;
		this->walls = walls;
		sprite = new Sprites(L"test.png", gfx);
	}

	



	void Update(double timeDelta, double timeTotal) override
	{
		//for (Bullets* n : bullets) n->Update(timeDelta);
		CalcDistance();
		if (able_to_see())
		{
			if (decide_to_move())
			{
				move(timeDelta);
			}
			else 
			{
				Bullets* bull = Shoot(timeTotal);
				if(bull!=nullptr) bullets.push_back(bull);

			}
		}
		for (Bullets* n : bullets) n->Update(timeDelta, timeTotal);
	}
	
	void Render() override
	{
		sprite->DrawAtPlace(x, y);
		for(Bullets* n : bullets) n->Render();
	}
	/*bool Touch() override;
	bool Touched() override;*/
};

