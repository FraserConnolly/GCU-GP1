#pragma once
#include "GameScene.h"
#include "Paddle.h" // player
#include "Block.h"
#include "Ball.h"
#include "PowerUp.h"
#include "Ground.h"
#include "UiText.h"

#define BLOCK_MAX_COUNT 100

#define BALL_COUNT_MAX 20
#define BALL_STARTING_SPEED 30

#define POWER_UP_MAX_COUNT 10
#define POWER_UP_SPEED 18

class ParanoidGameMainScene :
	public GameScene
{
public:

	ParanoidGameMainScene() :
		m_ground(160),
		m_scoreText("Score: %i", 100)
	{ }

	~ParanoidGameMainScene() override
	{ }

	void initaliseGame( int lastGameSceneResponse ) override;
	void updateGame( ) override;
	void drawGame() override;
	int loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively ) override;
	
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
	void tryLaunchPowerUp ( const Vector2Int & launchPoint );

	/* Game specific member variables */
	Paddle  m_paddle;
	Block   m_blocks   [ BLOCK_MAX_COUNT    ];
	Ball    m_balls    [ BALL_COUNT_MAX     ];
	PowerUp m_powerUps [ POWER_UP_MAX_COUNT ];
	Ground  m_ground;

	UiText m_scoreText;

	int m_score = 0;
	int m_level = 0;
	float m_levelStartTime = 0;

};

