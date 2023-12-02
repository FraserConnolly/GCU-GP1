#pragma once

// forward declaration 
class AliensGameSource;

class Player
	: public GameObject
{
public:
	Player ( ) : GameObject ( 1, 1 )
	{ 
		m_symbol [ 0 ].Char = '#';
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

	float fireTimeout = float(0.8);
	float m_lastFireTime = 0;

	void processMovement ( AliensGameSource * game );
	void processCombat   ( AliensGameSource * game );

};

