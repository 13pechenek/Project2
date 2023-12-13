#include "Player.h"

Player::Player(float x, float y, Graphics* gfx)
{
	sprite = new Sprites(L"test.png", gfx);
	this->x = x;
	this->y = y;
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


void Player::Update(double timeDelta, KeyDirections key)
{
	Move(key, timeDelta);
	return;
}


void Player::Render()
{
	(*sprite).DrawAtPlace(x, y);
}


bool Player::Death()
{
	return lives == 0;
}