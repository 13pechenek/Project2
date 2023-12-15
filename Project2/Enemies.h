#pragma once
#include <cmath>
#include "Objects.h"
#include "GameController.h"
#include "Player.h"
#include "Bullets.h"

class Enemies : Objects
{

private:
	ID2D1RectangleGeometry* rectangle;
	ID2D1TransformedGeometry* ray;
	Sprites* sprite;
	Graphics* gfx;
	Player* player;
	std::vector<Walls*>::iterator walls;
	std::vector<Bullets*> bullets;
	int countOfBullets = 10;
	int lives = 1;
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
		ray = gfx->GetRay(x,y,player->GetCoordinate());
		for (int i = 0; walls[i] != nullptr; i++) if(Overlapped(walls[i], ray)) return true;
		return false;
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
			std::vector<Enemies*>::iterator it;
			return new Bullets(x + 25, y + 17, player->GetCoordinate(), gfx, it, walls, player);
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
	ID2D1RectangleGeometry* geometry;
	Enemies(float x, float y, Player* player, std::vector<Walls*>::iterator walls, Graphics* gfx)
	{
		this->gfx = gfx;
		this->x = x; 
		this->y = y;
		this->player = player;
		this->walls = walls;
		sprite = new Sprites(L"test.png", gfx);
		geometry = sprite->geometry;
	}


	
	void Update(double timeDelta, double timeTotal) override
	{
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
		for (Bullets* n : bullets) n->PlayerTouched();
		geometry = gfx->MoveGeometry(x, y, geometry);
	}
	
	void Render() override
	{
		sprite->DrawAtPlace(x, y);
		gfx->GetRenderTarget()->FillGeometry(ray, gfx->SetBrush());
		for(Bullets* n : bullets) n->Render();
		gfx->GetRenderTarget()->FillGeometry(geometry, gfx->SetBrush());

	}
	bool Overlapped(Walls* wall, ID2D1TransformedGeometry* ray);

	bool Damaged()
	{
		lives--;
		return lives;
	}


};

