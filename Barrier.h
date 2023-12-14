#pragma once
#include "GameObject.h"

#define BARRIER_CELL_WIDTH 2
#define BARRIER_CELL_HEIGHT 1

class Barrier
	: public GameObject
{
public:

	Barrier ( ) : GameObject ( BARRIER_CELL_WIDTH, BARRIER_CELL_HEIGHT )
	{
		for ( size_t i = 0; i < (size_t) ( m_width * m_height ); i++ )
		{
			m_symbol [ i ].UnicodeChar = 0x2588;
			m_symbol [ i ].Attributes = CellColour::Fore_Green;
		}

		setActive ( false );
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return (pRenderCellData) m_symbol;
	};

	void onCollision(const GameObject& collision, const Point& collisionPoint) override
	{
		setActive(false);
	}

private:
	RenderCellData m_symbol [ BARRIER_CELL_WIDTH * BARRIER_CELL_HEIGHT ];
};

