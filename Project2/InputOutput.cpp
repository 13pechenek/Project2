#include "InputOutput.h"
#include "GameStructs.h"
#include <fstream>



void InputOutput::Input(Graphics* gfx, SinglyLinkedList<Walls*>* w, SinglyLinkedList<Enemies*>* e, Player* player)
{



	char input[30];
	std::fstream stream("lvl.txt");
	stream.getline(input, 30, ' ');
	int mult;

	int countWalls = 0;
	for (int i = stream.gcount() - 2; i >= 0; i--)
	{
		mult = 1;
		countWalls += (input[i] - '0') * mult;
		mult *= 10;
	}

	stream.getline(input, 30, '\n');
	int countEnemies = 0;
	for (int i = stream.gcount() - 2;  i>=0; i--)
	{
		mult = 1;
		countEnemies += (input[i] - '0')*mult;
		mult *= 10;
	}



	stream.getline(input, 30, ' ');
	int xplayer = 0;
	for (int i = stream.gcount() - 2; i >= 0; i--)
	{
		mult = 1;
		xplayer += (input[i] - '0') * mult;
		mult *= 10;
	}

	stream.getline(input, 30, '\n');
	int yplayer = 0;
	for (int i = stream.gcount() - 2; i >= 0; i--)
	{
		mult = 1;
		yplayer += (input[i] - '0') * mult;
		mult *= 10;
	}

	player = new Player(xplayer, yplayer, gfx);

	for (int i = 0; i < countWalls; i++)
	{
		stream.getline(input, 30, ' ');
		int left = 0;

		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			mult = 1;
			left += (input[i] - '0') * mult;
			mult *= 10;
		}

		stream.getline(input, 30, ' ');
		int top = 0;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			mult = 1;
			top += (input[i] - '0') * mult;
			mult *= 10;
		}

		stream.getline(input, 30, ' ');
		int right = 0;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			mult = 1;
			right += (input[i] - '0') * mult;
			mult *= 10;
		}

		stream.getline(input, 30, '\n');
		int bottom = 0;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			mult = 1;
			bottom += (input[i] - '0') * mult;
			mult *= 10;
		}

		w->append(new Walls(left, top, right, bottom, gfx));
	}

	for (int i = 0; i < countEnemies; i++)
	{
		stream.getline(input, 30, ' ');
		int xenemy = 0;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			mult = 1;
			xenemy += (input[i] - '0') * mult;
			mult *= 10;
		}

		stream.getline(input, 30, '\n');
		int yenemy = 0;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			mult = 1;
			yenemy += (input[i] - '0') * mult;
			mult *= 10;
		}

		e->append(new Enemies(xenemy, yenemy, player, , gfx));
	}
}


void InputOutput::Output()
{

}

void InputOutput::Init()
{

}
void InputOutput::Distruct()
{
}