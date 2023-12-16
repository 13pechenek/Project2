#include "Bullets.h"
#include "Player.h"
#include "Enemies.h"


Bullets::Bullets(float x, float y, POINT* aimPos, Graphics* gfx, SinglyLinkedList<Enemies*>* enemies, SinglyLinkedList<Walls*>* walls, Player* player)
{
	this->enemies = enemies;
	this->walls = walls;
	this->player = player;
	this->gfx = gfx;
	this->x = x;
	this->y = y;
	this->aimPos = aimPos;
	distanceToPoint = sqrt(pow((aimPos->x - x), 2) + pow((aimPos->y - y), 2));
	if (distanceToPoint == 0) return;
	Cosin = (aimPos->x - this->x) / distanceToPoint;
	Sinus = (aimPos->y - this->y) / distanceToPoint;
	geometry = gfx->GetEllipseGeometry(x, y, 2.5, 2.5);
}

void Bullets::Update(double timeDelta, double timeTotal)
{
	move(timeDelta);

}
void Bullets::Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mPosition)
{
	return;
}

void Bullets::move(double timeDelta)
{

	if (!distanceToPoint) return;
	x += v * Cosin * timeDelta;
	y += v * Sinus * timeDelta;
}

void Bullets::ResetDistance()
{
	distanceToPoint = sqrt(pow((aimPos->x - x), 2) + pow((aimPos->y - y), 2));
}

void Bullets::Render()
{
	gfx->DrawCircle(x, y, 2.5, 1, 1, 1, 1);
	geometry = gfx->MoveGeometry(x, y, geometry);
	gfx->GetRenderTarget()->FillGeometry(geometry, gfx->SetBrush());
}

bool Bullets::EnemyTouched()
{
	D2D1_GEOMETRY_RELATION* relation = new D2D1_GEOMETRY_RELATION;
	for (int i = 0; enemies->out(i)->data != nullptr; i++) 
	{
		geometry->CompareWithGeometry(enemies->out(i)->data->geometry, NULL, relation);
		if (*relation != D2D1_GEOMETRY_RELATION_DISJOINT)
		{
			enemies->out(i)->data->Damaged();
			enemies->removeAt(i);
			i--;
			return true;
		}
	}
	return false;
}

bool Bullets::PlayerTouched()
{
	D2D1_GEOMETRY_RELATION* relation = new D2D1_GEOMETRY_RELATION;
	geometry->CompareWithGeometry(player->geometry, NULL, relation);
		if (*relation != D2D1_GEOMETRY_RELATION_DISJOINT)
		{
			player->Damaged();
			return true;
		}
	return false;
}


bool Bullets::WallTouched()
{
	D2D1_GEOMETRY_RELATION* relation = new D2D1_GEOMETRY_RELATION;
	for (int i = 0; walls->out(i)->data != nullptr; i++)
	{
		geometry->CompareWithGeometry(walls->out(i)->data->geometry, NULL, relation);
		if (*relation != D2D1_GEOMETRY_RELATION_DISJOINT)
		{
			return true;
		}
	}
	return false;
}

Bullets::~Bullets()
{
	geometry->Release();
}

