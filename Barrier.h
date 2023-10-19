#pragma once
#include "GameObject.h"

class Barrier
	: public GameObject
{
public:

	Barrier() : GameObject ( 5, 1 ), symbol("*****")
	{

	}

	// Inherited via GameObject
	char* draw() override
	{
		return symbol;
	};

private:
	char symbol[6];
};

