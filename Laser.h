#pragma once
#include "Projectile.h"

/// <summary>
/// Lasers are fired by the player.
/// </summary>
class Laser 
	: public Projectile
{
public : 
	Laser ( ) : Projectile ( 0, -1 ), m_symbol ( "^" )
	{ }

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return m_symbol;
	}

private:
	char m_symbol [ 2 ];
};

