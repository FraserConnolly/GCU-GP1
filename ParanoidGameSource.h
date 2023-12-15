#pragma once
#include "GameSource.h"
#include "Paddle.h" // player
#include "Block.h"
#include "Ball.h"
#include "PowerUp.h"
#include "Ground.h"
#include "UiText.h"

#define BLOCK_MAX_COUNT 100

#define BALL_COUNT_MAX 20
#define BALL_STARTING_SPEED 20

#define POWER_UP_MAX_COUNT 10
#define POWER_UP_SPEED 18

class ParanoidGameSource :
	public GameSource
{
public:

	ParanoidGameSource() :
		m_ground(160),
		m_scoreText("Score: %i", 100),
		m_frameCountText("FPS: %f", 25)
	{ }

	~ParanoidGameSource() override
	{ }

	void initaliseGame() override;
	void updateGame( ) override;
	void drawGame() override;
	
	bool getHasStarted() const
	{
		return m_levelStartTime != 0;
	}

	void startLevel();

	Ball* const getAvilableBall();
	PowerUp* const getAvilablePowerUp();


protected:
	void initaliseLevel( ) override;

private:

	/* Game specific member functions */
	void tryLaunchPowerUp ( const Point & launchPoint );

	/* Game specific member variables */
	Paddle  m_paddle;
	Block   m_blocks   [ BLOCK_MAX_COUNT    ];
	Ball    m_balls    [ BALL_COUNT_MAX     ];
	PowerUp m_powerUps [ POWER_UP_MAX_COUNT ];
	Ground  m_ground;

	UiText m_scoreText;

	/* For debugging */
	UiText m_frameCountText;


	int m_score = 0;
	int m_level = 1;
	float m_levelStartTime = 0;

	void playMuisc( );

};

