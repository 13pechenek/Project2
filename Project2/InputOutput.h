#pragma once
#include <fstream>
#include "Level1.h"

class InputOutput
{
public:
	static void Input(Graphics* gfx, SinglyLinkedList<Walls*>* w, SinglyLinkedList<Enemies*>* e, Player** player);
	static void Output();
	static void Init();
	static void Distruct();
};

