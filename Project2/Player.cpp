#include "Player.h"


Player::Player(float x, float y, Graphics* gfx)
{
	sprite = new Sprites(L"test.png", gfx);
	this->x = x;
	this->y = y;
	mPoint.x = 0;
	mPoint.y = 0;
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


POINT Player::GetCoordinate()
{
	POINT point;
	point.x = x;
	point.y = y;
	return point;
}


Bullets* Player::Shoot()
{
	return new Bullets(x, y, mPoint);
}


void Player::Update(double timeDelta, KeyDirections key, POINT mPoint)
{
	Move(key, timeDelta);
	if (mPoint.x != 0 && mPoint.y != 0) bullets.push_back(Shoot());
	for (Bullets* n : bullets) n->Update(timeDelta);
	return;
}


void Player::Update(double timeDelta)
{
	return;
}


void Player::Render()
{
	(*sprite).DrawAtPlace(x, y);
	for (Bullets* n : bullets) n->Render();
}


bool Player::Death()
{
	return lives == 0;
}