#pragma once
#include "Projectile.h"

/// <summary>
/// Bombs are dropped by the aliens (AI).
/// </summary>
class Bomb
	: public Projectile
{
public:
	Bomb ( ) : Projectile( 0, 1 ), symbol ( "!" )
	{ }

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return symbol;
	}


private:
	char symbol [ 2 ];
};

