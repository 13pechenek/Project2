#pragma once

#include "GameLevel.h"
#include "Walls.h"
#include "Enemies.h"

class InputOutput;

class Level1 : public GameLevel
{
private:
	SinglyLinkedList<Walls*> w;
	SinglyLinkedList<Enemies*> e;
	Sprites* backgroung = new Sprites(L"Background.jpg", gfx);
public:
	Player* player;
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void Update(double timeTotal, double timeDelta, KeyDirections key, POINT* Mpostion) override;
};