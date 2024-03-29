#pragma once
#include "Projectile.h"

/// <summary>
/// Bombs are dropped by the aliens (AI).
/// </summary>
class Bomb
	: public Projectile
{
public:

	Bomb ( ) : Projectile( 0.0f, 1.0f )
	{ 
		m_symbol [ 0 ].UnicodeChar = 0x25CF;
		m_symbol [ 0 ].Attributes = CellColour::Fore_Yellow;
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return m_active ? ( pRenderCellData ) m_symbol : nullptr;
	}

	void onCollision ( const GameObject & collision, const Vector2Int & collisionPoint ) override
	{
		setActive ( false );
	}

private:
	RenderCellData m_symbol [ 1 ];
};

