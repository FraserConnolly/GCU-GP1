#pragma once
#include "GameSource.h"
#include "Alien.h"
#include "Barrier.h"
#include "Ground.h"
#include "Laser.h"
#include "Bomb.h"
#include "Player.h"
#include "UiText.h"

#define ALIENT_COUNT ALIEN_ROW_COUNT * ALIEN_COL_COUNT
#define BARRIER_COUNT 5
#define MAX_LASER_COUNT 3
#define MAX_BOMB_COUNT 5

/// <summary>
/// Reference game https://freeinvaders.org/
/// </summary>
class AliensGameSource :
	public GameSource
{
public:

	AliensGameSource ( ) : 
		m_ground ( 160 ),
		m_scoreText ( "Score: %i", 100 ),
		m_previousMovement( MovementDirection::DOWN )
	{ }

	~AliensGameSource ( ) override
	{ }

	void initaliseGame ( ) override;

	Laser * const getAvilableLaser();
	Bomb  * const getAvilableBomb ();

protected:
	
	void initaliseLevel( ) override;
	void updateGame ( ) override;
	void drawGame ( ) override;

private:

	enum MovementDirection
	{
		DOWN,
		LEFT,
		RIGHT
	}m_previousMovement;

	/* Game specific member functions */
	void setAlienPositions ( );
	void updateEdgeAlienPointers( );
	void setBarrierPositions ( );

	/* Game specific member variables */
	Player m_player;
	Alien m_aliens [ ALIENT_COUNT ];
	Barrier m_barriers [ BARRIER_COUNT ];
	Laser m_lasers [ MAX_LASER_COUNT ];
	Bomb m_bombs [ MAX_BOMB_COUNT ];
	Ground m_ground;

	UiText m_scoreText;

	int m_score = 0;
	int m_level = 0;
	float m_lastAlienMoveTime = 0;
	float m_alienMoveTimeout = 0;

	void playMuisc ( );
};

