#pragma once

#define PLAYER_FIRE_TIMEOUT 0.2f

// forward declaration 
class AliensGameSource;

class Player
	: public GameObject
{
public:
	Player ( ) : GameObject ( 1, 1 )
	{ 
		m_symbol [ 0 ].UnicodeChar = 0x2660;//'#';
		m_symbol [ 0 ].Attributes = CellColour::Fore_Cyan;
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return m_active ? ( pRenderCellData ) m_symbol : nullptr;
	};

	void onCollision ( const GameObject & collision, const Point collisionPoint ) override
	{
		setActive ( false );
	}

	void tick ( AliensGameSource * game );

private:
	RenderCellData m_symbol [ 1 ];

	float fireTimeout = PLAYER_FIRE_TIMEOUT;
	float m_lastFireTime = 0;

	void processMovement ( AliensGameSource * game );
	void processCombat   ( AliensGameSource * game );

};

