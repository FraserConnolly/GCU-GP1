#pragma once
#include "GameObject.h"

#define PLAYER_FIRE_TIMEOUT 0.2f

// forward declaration 
class SpaceInvaderMainScene;

class Player
	: public GameObject
{
public:
	Player ( ) : GameObject ( 5, 3 )
	{ 

		// first row
		m_symbol[0].AsciiChar = ' ';
		m_symbol[1].AsciiChar = ' ';
		m_symbol[2].UnicodeChar = 0x25B2;
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

		for (int i = 0; i < (int) ( m_width * m_height ); i++)
		{
			m_symbol[ i ].Attributes = CellColour::Fore_Cyan;
		}

	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return m_active ? ( pRenderCellData ) m_symbol : nullptr;
	};

	void onCollision ( const GameObject & collision, const Vector2Int & collisionPoint ) override
	{
		setActive ( false );
	}

	void tick ( SpaceInvaderMainScene * game );

private:
	RenderCellData m_symbol [ 15 ];

	float fireTimeout = PLAYER_FIRE_TIMEOUT;
	float m_lastFireTime = 0;

	void processMovement ( SpaceInvaderMainScene * game );
	void processCombat   ( SpaceInvaderMainScene * game );

};

