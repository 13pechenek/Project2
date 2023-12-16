#include "InputOutput.h"
#include "GameStructs.h"
#include <fstream>



void InputOutput::Input(Graphics* gfx, SinglyLinkedList<Walls*>* w, SinglyLinkedList<Enemies*>* e, Player** player)
{



	char input[30];
	std::fstream stream("lvl.txt");
	stream.getline(input, 30, ' ');
	int mult;

	int countWalls = 0;
	mult = 1;
	for (int i = stream.gcount() - 2; i >= 0; i--)
	{

		countWalls += (input[i] - '0') * mult;
		mult *= 10;
	}

	stream.getline(input, 30, '\n');
	int countEnemies = 0;
	mult = 1;
	for (int i = stream.gcount() - 2;  i>=0; i--)
	{
		countEnemies += (input[i] - '0')*mult;
		mult *= 10;
	}



	stream.getline(input, 30, ' ');
	int xplayer = 0;
	mult = 1;
	for (int i = stream.gcount() - 2; i >= 0; i--)
	{

		xplayer += (input[i] - '0') * mult;
		mult *= 10;
	}

	stream.getline(input, 30, '\n');
	int yplayer = 0;
	mult = 1;
	for (int i = stream.gcount() - 2; i >= 0; i--)
	{

		yplayer += (input[i] - '0') * mult;
		mult *= 10;
	}

	*player = new Player(xplayer, yplayer, gfx);

	for (int i = 0; i < countWalls; i++)
	{
		stream.getline(input, 30, ' ');
		int left = 0;
		mult = 1;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			left += (input[i] - '0') * mult;
			mult *= 10;
		}

		stream.getline(input, 30, ' ');
		int top = 0;
		mult = 1;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			top += (input[i] - '0') * mult;
			mult *= 10;
		}

		stream.getline(input, 30, ' ');
		int right = 0;
		mult = 1;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			right += (input[i] - '0') * mult;
			mult *= 10;
		}

		stream.getline(input, 30, '\n');
		int bottom = 0;
		mult = 1;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{

			bottom += (input[i] - '0') * mult;
			mult *= 10;
		}

		w->append(new Walls(left, top, right, bottom, gfx));
	}

	for (int i = 0; i < countEnemies; i++)
	{
		stream.getline(input, 30, ' ');
		int xenemy = 0;
		mult = 1;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			xenemy += (input[i] - '0') * mult;
			mult *= 10;
		}

		stream.getline(input, 30, '\n');
		int yenemy = 0;
		mult = 1;
		for (int i = stream.gcount() - 2; i >= 0; i--)
		{
			yenemy += (input[i] - '0') * mult;
			mult *= 10;
		}

		e->append(new Enemies(xenemy, yenemy, *player, w, gfx));
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