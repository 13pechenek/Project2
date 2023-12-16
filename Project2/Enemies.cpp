#include "Enemies.h"
#include "Walls.h"


bool Enemies::Overlapped(Walls* wall, ID2D1TransformedGeometry* ray)
{
	D2D1_GEOMETRY_RELATION* relation = new D2D1_GEOMETRY_RELATION;
	ray->CompareWithGeometry(wall->geometry, NULL, relation);
	if (*relation == D2D1_GEOMETRY_RELATION_DISJOINT) return true;
	else return false;
}


bool Enemies::decide_to_move()
{
	if (distance_to_Player > 1000) return true; else return false;
}

bool Enemies::able_to_see()
{
	ray = gfx->GetRay(x, y, player->GetCoordinate());
	for (int i = 0; walls->out(i)->data != nullptr; i++) if (Overlapped(walls->out(i)->data, ray)) return true;
	return false;
}

void Enemies::move(double timeDelta)
{
	if (!distance_to_Player) return;
	float cos = (player->GetCoordinate()->x - this->x) / distance_to_Player;
	float sin = (player->GetCoordinate()->y - this->y) / distance_to_Player;
	this->x += v * cos * timeDelta;
	this->y += v * sin * timeDelta;
}

void Enemies::Reload(double timeTotal)
{
	if (lastShot + 5 < timeTotal && !countOfBullets) countOfBullets = 10;
	else return;
}


void Enemies::CalcDistance()
{
	this->distance_to_Player = sqrt(pow((player->GetCoordinate()->x - x), 2) + pow((player->GetCoordinate()->y - y), 2));
	return;
}


Bullets* Enemies::Shoot(double timeTotal)
{
	Reload(timeTotal);
	if (lastShot + 1 < timeTotal && countOfBullets)
	{
		lastShot = timeTotal;
		countOfBullets--;
		SinglyLinkedList<Enemies*> enem;
		return new Bullets(x + 25, y + 17, player->GetCoordinate(), gfx, enem , walls, player);
	}
	else return nullptr;
}

void Enemies::Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mpoint)
{

}

Enemies::Enemies(float x, float y, Player* player, SinglyLinkedList<Walls*>* walls, Graphics* gfx)
{
	this->gfx = gfx;
	this->x = x;
	this->y = y;
	this->player = player;
	this->walls = walls;
	sprite = new Sprites(L"test.png", gfx);
	geometry = sprite->geometry;
}

void Enemies::Update(double timeDelta, double timeTotal)
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
			if (bull != nullptr) bullets.push_back(bull);

		}
	}
	for (Bullets* n : bullets) n->Update(timeDelta, timeTotal);
	for (Bullets* n : bullets) n->PlayerTouched();
	geometry = gfx->MoveGeometry(x, y, geometry);
}

void Enemies::Render()
{
	sprite->DrawAtPlace(x, y);
	gfx->GetRenderTarget()->FillGeometry(ray, gfx->SetBrush());
	for (Bullets* n : bullets) n->Render();
	gfx->GetRenderTarget()->FillGeometry(geometry, gfx->SetBrush());

}

bool Enemies::Damaged()
{
	lives--;
	return lives;
}

Enemies::~Enemies()
{
	delete sprite;
	for (Bullets* n : bullets) if (n != nullptr) delete n;
	geometry->Release();
	rectangle->Release();
	ray->Release();
}


