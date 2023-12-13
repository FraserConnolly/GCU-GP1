#pragma once
#include "GameObject.h"

#define PLAYER_FIRE_TIMEOUT 0.2f

// forward declaration 
class AliensGameSource;

class Player
	: public GameObject
{
public:
	Player ( ) : GameObject ( 5, 3 )
	{ 

		//    A
		//  |/|\|
		//  / | \

		// first row
		m_symbol[0].AsciiChar = ' ';
		m_symbol[1].AsciiChar = ' ';
		m_symbol[2].AsciiChar = 'A';
		m_symbol[3].AsciiChar = ' ';
		m_symbol[4].AsciiChar = ' ';
		// second row
		m_symbol[5].AsciiChar = '|';
		m_symbol[6].AsciiChar = '/';
		m_symbol[7].AsciiChar = '|';
		m_symbol[8].AsciiChar = '\\';
		m_symbol[9].AsciiChar = '|';
		// third row
		m_symbol[10].AsciiChar = '/';
		m_symbol[11].AsciiChar = ' ';
		m_symbol[12].AsciiChar = '|';
		m_symbol[13].AsciiChar = ' ';
		m_symbol[14].AsciiChar = '\\';

		for (size_t i = 0; i < (size_t)(m_width * m_height); i++)
		{
			m_symbol[i].Attributes = CellColour::Fore_Cyan;
		}

	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return m_active ? ( pRenderCellData ) m_symbol : nullptr;
	};

	void onCollision ( const GameObject & collision, const Point & collisionPoint ) override
	{
		setActive ( false );
	}

	void tick ( AliensGameSource * game );

private:
	RenderCellData m_symbol [ 15 ];

	float fireTimeout = PLAYER_FIRE_TIMEOUT;
	float m_lastFireTime = 0;

	void processMovement ( AliensGameSource * game );
	void processCombat   ( AliensGameSource * game );

};

