#pragma once
#include "GameObject.h"

class Barrier
	: public GameObject
{
public:

	Barrier ( ) : GameObject ( 5, 1 )
	{
		for ( size_t i = 0; i < size_t ( m_width * m_height ); i++ )
		{
			m_symbol [ i ].UnicodeChar = '*';
			m_symbol [ i ].Attributes = CellColour::Fore_Red;
		}
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return (pRenderCellData) m_symbol;
	};

private:
	RenderCellData m_symbol [ 6 ];
};

