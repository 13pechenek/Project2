#pragma once

#include "GameLevel.h"
#include "Objects.h"
#include "Walls.h"
#include "Enemies.h"

class InputOutput;

class Level1 : public GameLevel
{
private:
	SinglyLinkedList<Walls*> w;
	SinglyLinkedList<Enemies*> e;
	double vec[2]{ 0.0, 0.0 };
public:


	Player* player;
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeTotal, double timeDelta) override;
	void Update(double timeTotal, double timeDelta, KeyDirections key, POINT* Mpostion) override;
};