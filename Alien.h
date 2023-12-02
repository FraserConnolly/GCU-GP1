#pragma once
#include "GameObject.h"

class Alien
	: public GameObject
{
public:

	Alien ( ) : GameObject ( 3, 3 )
	{
		//   XXX
		//   X|X
		//   X X

		// first row
		m_symbol [ 0 ].Char = 'X';
		m_symbol [ 1 ].Char = 'X';
		m_symbol [ 2 ].Char = 'X';
		// second row
		m_symbol [ 3 ].Char = 'X';
		m_symbol [ 4 ].Char = '|';
		m_symbol [ 5 ].Char = 'X';
		// third row
		m_symbol [ 6 ].Char = 'X';
		m_symbol [ 7 ].Char = ' ';
		m_symbol [ 8 ].Char = 'X';

		for ( size_t i = 0; i < m_width * m_height; i++ )
		{
			m_symbol [ i ].Attributes = CellColour::Fore_Red;
		}
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return m_active ? (pRenderCellData) m_symbol : nullptr;
	};

	void onCollision ( const GameObject & collision, const Point collisionPoint ) override
	{
		setActive ( false );
	}

private:
	RenderCellData m_symbol [ 9 ];
};

