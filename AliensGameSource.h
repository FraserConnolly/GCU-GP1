#pragma once
#include "GameSource.h"
#include "Alien.h"
#include "Barrier.h"
#include "Ground.h"
#include "Laser.h"
#include "Bomb.h"
#include "Player.h"

#define ALIENT_COUNT 20
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

	AliensGameSource ( ) : m_ground ( 160 )
	{ }

	void initaliseGame ( ) override;
	void updateGame( ) override;
	void drawGame ( ) override;

	void setAlientPositions ( );
	void setBarrierPositions ( );

	Laser * getAvilableLaser ( ) const;

protected:
	void drawGameObjects ( );

private:

	/* Game specific member functions */

	/* Game specific member variables */
	Player m_player;
	Alien m_aliens [ ALIENT_COUNT ];
	Barrier m_barriers [ BARRIER_COUNT ];
	Laser m_lasers [ MAX_LASER_COUNT ];
	Bomb m_bombs [ MAX_BOMB_COUNT ];
	Ground m_ground;

	float playerMoveTimer = 0;

	void playMuisc ( );
};

