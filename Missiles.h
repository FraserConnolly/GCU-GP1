#pragma once
#include "GameObject.h"

class Missiles 
	: public GameObject
{
	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return nullptr;
	}
};

