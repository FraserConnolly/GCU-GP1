#pragma once
#include <iostream>
#include "GameObject.h"

#define MAX_GROUND_SIZE 300

class Ground
	: public GameObject
{

public:

	Ground ( int width ) : GameObject ( width, 1 )
	{
		if ( width > MAX_GROUND_SIZE )
		{
			m_width = MAX_GROUND_SIZE;
		}

		for ( unsigned int i = 0; i < MAX_GROUND_SIZE; i++ )
		{
			m_symbol [ i ].UnicodeChar = i < m_width ? 0x2500 : 0x0000;
			m_symbol [ i ].Attributes  = i < m_width ? CellColour::Fore_Green : 0 ;
		}
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return m_active ? ( pRenderCellData ) m_symbol : nullptr;
	};

private:

	RenderCellData m_symbol [ MAX_GROUND_SIZE ];

};
