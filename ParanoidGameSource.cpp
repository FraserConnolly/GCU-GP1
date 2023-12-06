#include "ParanoidGameSource.h"

void ParanoidGameSource::initaliseGame()
{
	GameSource::initaliseGame();

	initaliseLevel();

	m_paddle.setGridPosition(getScreenWidth() / 2, 40);

	m_ground.setGridPosition(0, 42);

	m_scoreText.setGridPosition(5, 43);

	m_keyboardInput.registerKey(VK_SPACE);
	m_keyboardInput.registerKey(VK_LEFT);
	m_keyboardInput.registerKey(VK_RIGHT);

}

void ParanoidGameSource::updateGame ( )
{ 
	GameSource::updateGame ( );

	// check for level over condition
	bool allBallsLost = true;

	for (Ball& ball : m_balls)
	{
		if (ball.getActive())
		{
			allBallsLost = false;
			break;
		}
	}

	if (allBallsLost)
	{
		// level over - lose
		GameSource::quit( );
		return;
	}

	bool allBlocksDestroyed = true;

	for (Block& block : m_blocks)
	{
		if (block.getActive())
		{
			allBlocksDestroyed = false;
			break;
		}
	}

	if (allBlocksDestroyed)
	{
		// level over - win
		initaliseLevel( );
		return;
	}

	m_paddle.tick(this);

	for (Ball& ball : m_balls)
	{
		ball.tick(this);
	}

}

void ParanoidGameSource::drawGame()
{
	GameSource::quit ( );
}

void ParanoidGameSource::startLevel()
{
	if (getHasStarted())
	{
		// can not start a level which has already started
		return;
	}

	m_levelStartTime = gameTime;

	Ball* firstBall = getAvilableBall();

	if (firstBall == nullptr)
	{
		throw;
	}

	// launch the ball from above the center of the paddle
	firstBall->launch(
		Point(m_paddle.getGridX() + (m_paddle.getWidth() / 2),
			m_paddle.getGridY() - 1),
		BALL_STARTING_SPEED
	);
}

Ball* const ParanoidGameSource::getAvilableBall()
{
	for (int i = 0; i < BALL_MAX_COUNT; i++)
	{
		Ball* const ball = &m_balls[i];

		if (!ball->getActive())
		{
			return ball;
		}
	}

	return nullptr;
}

PowerUp* const ParanoidGameSource::getAvilablePowerUp()
{
	for (int i = 0; i < POWER_UP_MAX_COUNT; i++)
	{
		PowerUp* const powerUp = &m_powerUps[i];

		if (!powerUp->getActive())
		{
			return powerUp;
		}
	}

	return nullptr;
}

void ParanoidGameSource::initaliseLevel( )
{
	// set the position of each block depending on which level is loading.

	// disable all balls and power ups
	for (Ball& ball : m_balls)
	{
		ball.setActive(false);
	}

	for (PowerUp& powerUps : m_powerUps)
	{
		powerUps.setActive(false);
	}

	// to do disable any power ups
	m_paddle.resetPowerUps();
}

void ParanoidGameSource::playMuisc( )
{
}
