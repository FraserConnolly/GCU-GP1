#pragma once
#include "GameObject.h"

/// <summary>
/// Each alien will only survive one hit from the player's laser.
/// Aliens will only increase speed when they drop down a row.
/// Aliens will only drop down a row when the left/right most alien reaches
/// the edge of the screen.
/// </summary>
class Alien
	: public GameObject
{

#define ALIEN_START_ROW_MIN 3
#define ALIEN_START_ROW_MAX 25
#define ALIEN_EDGE_PADDING 5

#define ALIEN_X_TRANSLATION 3
#define ALIEN_Y_TRANSLATION 2

#define ALIEN_ROW_HEIGHT 5
#define ALIEN_ROW_COUNT 5
#define ALIEN_COL_COUNT 10

// Timeouts are floats in seconds.
#define ALIEN_MOVEMENT_TIMEOUT_MAX 1.4f
#define ALIEN_MOVEMENT_TIMEOUT_MIN 0.4f
#define ALIEN_MOVEMENT_TIMEOUT_DECREMENT 0.2f
#define ALIEN_HIT_SCORE 100

public:

	Alien ( ) : GameObject ( 5, 3 )
	{
		//  \ | /
		//  |\|/|
		//    V

		// first row
		m_symbol [ 0 ].AsciiChar = '\\';
		m_symbol [ 1 ].AsciiChar = ' ';
		m_symbol [ 2 ].AsciiChar = '|';
		m_symbol [ 3 ].AsciiChar = ' ';
		m_symbol [ 4 ].AsciiChar = '/';
		// second row
		m_symbol [ 5 ].AsciiChar = '|';
		m_symbol [ 6 ].AsciiChar = '\\';
		m_symbol [ 7 ].AsciiChar = '|';
		m_symbol [ 8 ].AsciiChar = '/';
		m_symbol [ 9 ].AsciiChar = '|';
		// third row
		m_symbol [ 10 ].AsciiChar = ' ';
		m_symbol [ 11 ].AsciiChar = ' ';
		m_symbol [ 12 ].UnicodeChar = 0x25BC;
		m_symbol [ 13 ].AsciiChar = ' ';
		m_symbol [ 14 ].AsciiChar = ' ';

		for ( size_t i = 0; i < (size_t) ( m_width * m_height ); i++ )
		{
			m_symbol [ i ].Attributes = CellColour::Fore_White;
		}
	}

	// Inherited via GameObject
	const pRenderCellData draw ( ) const override
	{
		return m_active ? (pRenderCellData) m_symbol : nullptr;
	};

	void onCollision ( const GameObject & collision, const Point & collisionPoint ) override
	{
		setActive ( false );
	}

#pragma region Static Methods

	static int getStartRow();
	static void setStartRow( const int startRow );

	static void setEdgeAliens(const Alien* const leftAlien, const Alien* const rightAlien);
	static void getEdgeAlienColumns(int& leftColumn, int& rightColumn);

	/// <summary>
	/// This function returns the next timeout that the game should use for alien movement.
	/// It also reduces the timeout that will be returned the next time this method is called.
	/// Make sure to only call this methods when the aliens have moved or else the 
	/// aliens will move more frequently than expected.
	/// </summary>
	/// <returns>The timeout before the next alien movement is allowed.</returns>
	static float getMovementTimeout();

	static void resetGame( );

#pragma endregion

private:
	RenderCellData m_symbol[15];
	
	static int s_startRow;
	static int s_timeoutCalls;
	static const Alien* s_leftMostAlien;
	static const Alien* s_rightMostAlien;

};

