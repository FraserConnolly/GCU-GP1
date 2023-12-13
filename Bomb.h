#pragma once
#include "Projectile.h"

/// <summary>
/// Bombs are dropped by the aliens (AI).
/// </summary>
class Bomb
	: public Projectile
{
public:
	Bomb ( ) : Projectile( 0, 1 )
	{ 
		m_symbol [ 0 ].AsciiChar = '!';
		m_symbol [ 0 ].Attributes = CellColour::Fore_Red | CellColour::Back_Black;
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return m_active ? ( pRenderCellData ) m_symbol : nullptr;
	}

	void onCollision ( const GameObject & collision, const Point & collisionPoint ) override
	{
		setActive ( false );
	}

private:
	RenderCellData m_symbol [ 1 ];
};

