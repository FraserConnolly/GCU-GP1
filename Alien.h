#pragma once
#include "GameObject.h"

class Alien
	: public GameObject
{
public:

	Alien() : GameObject ( 1, 1 ), symbol("X")
	{

	}

	// Inherited via GameObject
	char* draw() override
	{
		return symbol;
	};

private:
	char symbol[2];
};

