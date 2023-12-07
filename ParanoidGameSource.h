#pragma once
#include "GameSource.h"
#include "Paddle.h" // player
#include "Block.h"
#include "Ball.h"
#include "PowerUp.h"
#include "Ground.h"
#include "UiText.h"

#define BLOCK_MAX_COUNT 100
#define BALL_MAX_COUNT 10
#define POWER_UP_MAX_COUNT 10
#define BALL_STARTING_SPEED 150


class ParanoidGameSource :
	public GameSource
{
public:

	ParanoidGameSource() : 
		m_ground(160), 
		m_scoreText("Score: %i", 100)
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

	/* Game specific member variables */
	Paddle  m_paddle;
	Block   m_blocks   [ BLOCK_MAX_COUNT    ];
	Ball    m_balls    [ BALL_MAX_COUNT     ];
	PowerUp m_powerUps [ POWER_UP_MAX_COUNT ];
	Ground  m_ground;

	UiText m_scoreText;

	int m_score = 0;
	int m_level = 0;
	float m_levelStartTime = 0;

	void playMuisc( );

};

