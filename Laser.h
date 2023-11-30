#pragma once
#include "GameObject.h"

class GameSource;

/// <summary>
/// Lasers are fired by the player.
/// </summary>
class Laser 
	: public GameObject
{
public : 
	Laser ( ) : GameObject ( 1, 1 ), m_symbol ( "^" )
	{ }

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return m_symbol;
	}

	void launch ( const COORD startGridPosition, const float speed );
	void tick ( GameSource * game );

	const bool getInFlight ( ) const
	{
		return m_isInFlight;
	}

private:
	char m_symbol [ 2 ];

	float m_speed;
	bool m_isInFlight = false;

};

