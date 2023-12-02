/*
* Created By: Fraser Connolly
* Created Date: 2023-10-12
*/

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
			m_symbol [ i ].Char = i < m_width ? '_' : '\0';
			m_symbol [ i ].Attributes = i < m_width ? CellColour::Fore_White : 0 ;
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
