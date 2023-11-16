#pragma once
#include "GameObject.h"

class Barrier
	: public GameObject
{
public:

	Barrier ( ) : GameObject ( 5, 1 ), symbol ( "*****" )
	{

	}

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return symbol;
	};

private:
	char symbol [ 6 ];
};

