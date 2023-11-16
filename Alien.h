#pragma once
#include "GameObject.h"

class Alien
	: public GameObject
{
public:

	Alien ( ) : GameObject ( 1, 1 ), symbol ( "X" )
	{

	}

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return symbol;
	};

private:
	char symbol [ 2 ];
};

