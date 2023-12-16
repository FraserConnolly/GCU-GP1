#pragma once
#include "Projectile.h"

/// <summary>
/// Lasers are fired by the player.
/// </summary>
class Laser 
	: public Projectile
{
public : 
	Laser ( ) : Projectile ( 0, -1 )
	{
		m_symbol [ 0 ].UnicodeChar = 0x25CF;
		m_symbol [ 0 ].Attributes = CellColour::Fore_Green;
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return ( pRenderCellData ) m_symbol;
	}

	void onCollision ( const GameObject & collision, const Vector2Int & collisionPoint ) override
	{
		setActive ( false );
	}

private:
	RenderCellData m_symbol [ 1 ];
};

