#include "Player.h"
#include "Enemies.h"

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
	sprite->DrawAtPlace(x, y);
	for (Bullets* n : bullets) n->Render();
	int i = 0;
	while (enemies[i] != nullptr)
	{
		enemies[i]->Render();
		i++;
	}
	
}


bool Player::Death()
{
	return lives == 0;
}