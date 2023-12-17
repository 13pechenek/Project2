#include "Player.h"
#include "Enemies.h"
#include "Walls.h"
#include "Bullets.h"


Player::Player(float x, float y, Graphics* gfx)
{
	this->gfx = gfx;
	sprite = new Sprites(L"Player.png", gfx);
	this->x = x;
	this->y = y;
	mPoint->x = 0;
	mPoint->y = 0;
	posit = new POINT;
	geometry = sprite->geometry;
}
void Player::Init(SinglyLinkedList<Walls*>* walls, SinglyLinkedList<Enemies*>* enemies)
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
	SetInTheBorders(timeDelta);
	y += v * timeDelta * vec[1];
	x += v * timeDelta * vec[0];
}

void Player::SetInTheBorders(double timeDelta)
{
	float dx = v * timeDelta * vec[0];
	float dy = v * timeDelta * vec[1];
	if (y + dy > 1045)
	{
		vec[1] = 0;
	}
	else if (y + dy< 0)
	{
		vec[1] = 0;
	}
	if (x + dx > 1870)
	{
		vec[0] = 0;
	}
	else if (x + dx < 0)
	{
		vec[0] = 0;
	}
	for (int i = 0; walls->out(i) != nullptr; i++)
	{
		Walls* wall = walls->out(i)->data;
		if (x + dx +49 > wall->left && x + dx < wall->left && y + dy   < wall->bottom && y + dy  > wall->top - 49)
		{
			vec[0] = 0;
		}
		else if (x + dx < wall->right && x + dx +49 > wall->right && y + dy   < wall->bottom && y + dy + 49 > wall->top)
		{
			vec[0] = 0;
		}
		if (y + dy + 49 > wall->bottom && y + dy < wall->bottom && x + dx + 49  > wall->left && x + dx < wall->right)
		{
			vec[1] = 0;
		}
		else if (y + dy  < wall->top && y + dy + 49 > wall->top && x + dx + 49 > wall->left && x + dx < wall->right)
		{
			vec[1] = 0;
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
		return new Bullets(x + 47, y + 31, mPoint, gfx, enemies, walls, nullptr, 1, 0, 0);
	}
	else return nullptr;
}


 void Player::Update(double timeDelta, double timeTotal, KeyDirections key, POINT* mPoint)
{
	int i = 0;
	while (enemies->out(i) != nullptr) 
	{
		enemies->out(i)->data->Update(timeDelta, timeTotal);
		i++;
	}
	i = 0;
	Move(key, timeDelta);
	geometry = gfx->MoveGeometry(x, y, geometry);
	this->mPoint = mPoint;
	for (int i = 0; bullets.out(i) != nullptr; i++) bullets.out(i)->data->Update(timeDelta);
	for (int i = 0; bullets.out(i) != nullptr; i++)  if(bullets.out(i)->data->EnemyTouched()) {delete bullets.out(i)->data; bullets.removeAt(i); i--; }
	for (int i = 0; bullets.out(i) != nullptr; i++)
	{
		if (bullets.out(i)->data->WallTouched())
		{
			delete bullets.out(i)->data;
			bullets.removeAt(i);
				i--; 
		} 
	}
	posit->x = x+25;
	posit->y = y+25;
	gfx->MoveGeometry(x, y, sprite->geometry);
	if (mPoint->x == 0 && mPoint->y == 0) return;
	Bullets* bullet = Shoot(timeTotal);
	if(bullet!=nullptr) bullets.append(bullet);
	return;
}


void Player::Update(double timeDelta, double timeTotal)
{
	return;
}


void Player::Render()
{
	
	for (int i = 0; bullets.out(i) != nullptr; i++) bullets.out(i)->data->Render();
	int i = 0;
	while (enemies->out(i) != nullptr)
	{
		enemies->out(i)->data->Render();
		i++;
	}
	for (i = 0; walls->out(i) != nullptr; i++) walls->out(i)->data->Render();
	sprite->DrawAtPlace(x, y);
}


bool Player::Death()
{
	return lives <= 0;
}

void Player::Damaged()
{
	lives--;
}

Player::~Player()
{
	delete sprite;
	delete posit;
	geometry->Release();
}



