#include "Player.h"
#include "Enemies.h"
#include "Walls.h"

Player::Player(float x, float y, Graphics* gfx)
{
	this->gfx = gfx;
	sprite = new Sprites(L"test.png", gfx);
	this->x = x;
	this->y = y;
	mPoint->x = 0;
	mPoint->y = 0;
	posit = new POINT;
	posit->x = x;
	sprite->geometry;
}
void Player::Init(std::vector<Walls*>::iterator walls, std::vector<Enemies*>::iterator enemies)
{
	this->walls = walls;
	this->enemies = enemies;
}


void Player::Move(KeyDirections key, double timeDelta)
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
	this->SetInTheBorders();
}

void Player::SetInTheBorders()
{
	if (y > 1045)
	{
		y = 1045;
	}
	else if (y < 0)
	{
		y = 0;
	}
	if (x > 1870)
	{
		x = 1870;
	}
	else if (x < 0)
	{
		x = 0;
	}
	for (int i = 0; walls[i] != nullptr; i++)
	{
		if (x +50 > walls[i]->left && x < walls[i]->left)
		{
			x = walls[i]->left - 50;
		}
		else if (x < walls[i]->right && x+50 > walls[i]->right)
		{
			x = walls[i]->right + 50;
		}
		if (y + 35 > walls[i]->bottom && y < walls[i]->bottom)
		{
			y = walls[i]->bottom + 35;
		}
		else if (y < walls[i]->top && y + 35 > walls[i]->top)
		{
			y = walls[i]->top - 35;
		}
	}

}


POINT* Player::GetCoordinate()
{
	return posit;
}

void Player::Reload(double timeTotal)
{
	if (lastShot + 5 < timeTotal && !countOfBullets) countOfBullets = 10;
	else return;
}

Bullets* Player::Shoot(double timeTotal)
{
	Reload(timeTotal);
	if (lastShot + 0.5 < timeTotal && countOfBullets) 
	{
		lastShot = timeTotal;
		countOfBullets--;
		return new Bullets(x + 47, y + 31, mPoint, gfx);
	}
	else return nullptr;
}


void Player::Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mPoint)
{
	int i = 0;
	while (enemies[i] != nullptr) 
	{
		enemies[i]->Update(timeDelta, timeTotal);
		i++;
	}
	Move(key, timeDelta);
	this->mPoint = mPoint;
	for (Bullets* n : bullets) n->Update(timeDelta, timeTotal);
	posit->x = x;
	posit->y = y;
	gfx->MoveGeometry(x, y, sprite->geometry);
	if (mPoint->x == 0 && mPoint->y == 0) return;
	Bullets* bullet = Shoot(timeTotal);
	if(bullet!=nullptr) bullets.push_back(bullet);
	return;
}


void Player::Update(double timeDelta, double timeTotal)
{
	return;
}


void Player::Render()
{
	
	for (Bullets* n : bullets) n->Render();
	int i = 0;
	while (enemies[i] != nullptr)
	{
		enemies[i]->Render();
		i++;
	}
	for (i = 0; walls[i] != nullptr; i++) walls[i]->Render();
	sprite->DrawAtPlace(x, y);
}


bool Player::Death()
{
	return lives == 0;
}

