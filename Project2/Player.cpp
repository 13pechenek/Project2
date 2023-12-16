#include "Player.h"
#include "Enemies.h"
#include "Walls.h"
#include "Bullets.h"


Player::Player(float x, float y, Graphics* gfx)
{
	this->gfx = gfx;
	sprite = new Sprites(L"test.png", gfx);
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
	for (int i = 0; walls != nullptr; i++)
	{
		if (x + dx +49 > walls[i]->left && x + dx < walls[i]->left && y + dy   < walls[i]->bottom && y + dy  > walls[i]->top-36)
		{
			vec[0] = 0;
		}
		else if (x + dx < walls[i]->right && x + dx +49 > walls[i]->right && y + dy   < walls[i]->bottom && y + dy + 36 > walls[i]->top)
		{
			vec[0] = 0;
		}
		if (y + dy + 36 > walls[i]->bottom && y + dy < walls[i]->bottom && x + dx + 49  > walls[i]->left && x + dx < walls[i]->right)
		{
			vec[1] = 0;
		}
		else if (y + dy  < walls[i]->top && y + dy + 36 > walls[i]->top && x + dx + 49 > walls[i]->left && x + dx < walls[i]->right)
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
		return new Bullets(x + 47, y + 31, mPoint, gfx, enemies, walls, nullptr);
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
	i = 0;
	Move(key, timeDelta);
	geometry = gfx->MoveGeometry(x, y, geometry);
	this->mPoint = mPoint;
	for (Bullets* n : bullets) if (n!=nullptr) n->Update(timeDelta, timeTotal);
	for (Bullets* n : bullets) if (n != nullptr) n->EnemyTouched();
	for (Bullets* n : bullets)
	{
		if (n != nullptr) 
		{ 
			if (n->WallTouched()) 
			{
				delete n;
				bullets.erase(bullets.begin() + i);
				i--; 
			} 
		}
			i++;
	}
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
	
	for (Bullets* n : bullets) if(n!=nullptr) n->Render();
	int i = 0;
	while (enemies[i] != nullptr)
	{
		enemies[i]->Render();
		i++;
	}
	for (i = 0; walls[i] != nullptr; i++) walls[i]->Render();
	sprite->DrawAtPlace(x, y);
	gfx->GetRenderTarget()->FillGeometry(geometry, gfx->SetBrush());
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



