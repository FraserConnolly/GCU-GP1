#pragma once

// forward declaration 
class AliensGameSource;

class Player
	: public GameObject
{
public:
	Player ( ) : GameObject ( 1, 1 ), playerSymbol ( "#" )
	{ }

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return playerSymbol;
	};

	void tick ( AliensGameSource * game );

private:
	char playerSymbol [ 2 ];

	float fireTimeout = float(0.8);
	float m_lastFireTime = 0;

	void processMovement ( AliensGameSource * game );
	void processCombat   ( AliensGameSource * game );

};

