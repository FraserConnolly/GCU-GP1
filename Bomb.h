#pragma once
#include "GameObject.h"

/// <summary>
/// Bombs are dropped by the aliens (AI).
/// </summary>
class Bomb
	: public GameObject
{
public:
	Bomb ( ) : GameObject ( 1, 1 ), symbol ( "@" )
	{ }

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return symbol;
	}

	void launch ( const COORD startGridPosition, const float speed );
	void tick ( GameSource * game );

	const bool getInFlight ( ) const
	{
		return m_isInFlight;
	}


private:
	char symbol [ 2 ];

	bool m_isInFlight = false;
	float m_speed = 0;
};

