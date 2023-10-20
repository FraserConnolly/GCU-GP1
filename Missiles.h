#pragma once
#include "GameObject.h"

class Missiles 
	: public GameObject
{
	// Inherited via GameObject
	char * draw ( ) override
	{
		return nullptr;
	}
};

