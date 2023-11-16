#pragma once
#include "GameObject.h"

class Player
	: public GameObject
{
public:
	Player ( ) : GameObject ( 1, 1 ), playerSymbol ( "^" )
	{ }

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return playerSymbol;
	};

private:
	char playerSymbol [ 2 ];
};

