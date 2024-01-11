#pragma once
#include "GameScene.h"
#include "Alien.h"
#include "Barrier.h"
#include "Ground.h"
#include "Laser.h"
#include "Bomb.h"
#include "Player.h"
#include "UiText.h"

#define ALIEN_COUNT ALIEN_ROW_COUNT * ALIEN_COL_COUNT
#define ALIEN_GOAL_ROW 37

#define BARRIER_COUNT_MAX BARRIER_COUNT_PER_BLOCK * BARRIER_BLOCK_COUNT
#define BARRIER_BLOCK_COUNT 8
#define BARRIER_COUNT_PER_BLOCK 15
#define BARRIER_BLOCK_EDGE_PADDING 12
#define BARRIER_BLOCK_GAP 7
#define BARRIER_ROW 34

#define LASER_COUNT_MAX 3

#define BOMB_COUNT_MAX 5
#define BOMB_DROP_TIMEOUT_MAX 4.0
#define BOMB_DROP_TIMEOUT_MIN 0.8
#define BOMB_SPEED 30

#define PLAYER_ROW 39

#define GROUND_ROW 42

#define SCORE_ROW 43

/// <summary>
/// Reference game https://freeinvaders.org/
/// </summary>
class SpaceInvaderMainScene :
	public GameScene
{
public:

	SpaceInvaderMainScene ( ) : 
		m_ground ( 160 ),
		m_scoreText ( "Score: %i", 100 ),
		m_previousMovement( MovementDirection::DOWN )
	{ }

	~SpaceInvaderMainScene ( ) override
	{ }

	void initaliseGame ( int lastGameSceneResponse ) override;
	int loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively ) override;

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
	void tryDropBomb( );

	/* Game specific member variables */
	Player m_player;
	Alien m_aliens [ ALIEN_COUNT ];
	Barrier m_barriers [ BARRIER_COUNT_MAX ];
	Laser m_lasers [ LASER_COUNT_MAX ];
	Bomb m_bombs [ BOMB_COUNT_MAX ];
	Ground m_ground;

	UiText m_scoreText;

	int m_score = 0;
	int m_level = 0;
	float m_nextAlienMoveTime = 0;
	float m_alienMoveTimeout = 0;
	float m_nextAlienBomb = BOMB_DROP_TIMEOUT_MAX;

	void playMuisc ( );
};

