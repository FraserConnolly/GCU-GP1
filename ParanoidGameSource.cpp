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

	if (getHasStarted())
	{
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
			GameSource::quit();
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
			initaliseLevel();
			return;
		}
	}

	m_paddle.tick(this);

	for (Ball& ball : m_balls)
	{
		ball.tick(this);
	}

	// check for collisions

	for (Ball& ball : m_balls)
	{
		bool hasCollided = false;

		if (!ball.getActive())
		{
			continue;
		}

		for (Block& block : m_blocks)
		{
			if (!block.getActive())
			{
				continue;
			}

			if (ball.hasCollided(block))
			{
				// collision
				ball .onCollision(block, ball.getGridPosition());
				block.onCollision(ball,  ball.getGridPosition());
				m_score += 10;

				if (!block.getActive())
				{
					// add an additional 20 points for destroying a block
					m_score += 20;
				}
				break;
			}
		}

		if (!ball.getActive())
		{
			continue;
		}

		if (ball.hasCollided(m_paddle))
		{
			ball.onCollision(m_paddle, ball.getGridPosition());
		}

		if (ball.hasCollided(m_ground))
		{
			ball.onCollision(m_ground, ball.getGridPosition());
		}
	}

	for (PowerUp& powerUp : m_powerUps)
	{
		if (!powerUp.getActive())
		{
			continue;
		}

		if (powerUp.hasCollided(m_paddle))
		{
			powerUp.setActive(false);
			m_paddle.applyPowerUp(powerUp.getPowerUp());
		}
	}

}

void ParanoidGameSource::drawGame()
{
	// populate the back buffer
	pRenderCellData toBeDrawn = nullptr;

	// Draw blocks
	GameSource::drawObjectsInArray(m_blocks, BLOCK_MAX_COUNT);

	// Draw balls
	GameSource::drawObjectsInArray(m_balls, BALL_MAX_COUNT);

	// Draw power ups
	GameSource::drawObjectsInArray(m_powerUps, POWER_UP_MAX_COUNT);

	// Draw player
	if (m_paddle.getActive())
	{
		drawGameObject(m_paddle);
	}

	// Draw ground
	if (m_ground.getActive())
	{
		drawGameObject(m_ground);
	}

	// Draw UI
	m_scoreText.updateText(m_score);
	if (m_scoreText.getActive())
	{
		drawGameObject(m_scoreText);
	}

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

	// set the direction to at a 45 degree angle from the paddle.
	firstBall->setDirection(1, -1);

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
	int levelIndex = m_level % 3; // 3 == number of levels
	CellColour colour;

	switch (levelIndex)
	{
	default:
	case 0:

		for (int i = 0, c = 0; c < 15; c++)
		{
			for (int r = 0; r < 6; r++, i++)
			{
				m_blocks[i].setActive(true);
				m_blocks[i].setGridPosition(5 + (c * m_blocks[i].getWidth()), 5 + (r* m_blocks[i].getHeight()));

				switch (i % 7)
				{
				default:
					colour = CellColour::Fore_Red;
					break;
				case 1:
					colour = CellColour::Fore_Green;
					break;
				case 2:
					colour = CellColour::Fore_Blue;
					break;
				case 3:
					colour = CellColour::Fore_Magenta;
					break;
				case 4:
					colour = CellColour::Fore_Cyan;
					break;
				case 5:
					colour = CellColour::Fore_Yellow;
					break;
				case 6:
					colour = CellColour::Fore_White;
					break;
				}


				m_blocks[i].setColour(colour);
			}
		}

		break;
	case 1:
		for (int i = 0, c = 0; c < 15; c++)
		{
			for (int r = 0; r < 6; r++, i++)
			{
				m_blocks[i].setActive(true);
				m_blocks[i].setGridPosition(5 + (c * m_blocks[i].getWidth()+1), 5 + (r * (m_blocks[i].getHeight()+1)));
			}
		}
		
		break;
	case 2:
		for (int i = 0, c = 0; c < 15; c++)
		{
			for (int r = 0; r < 6; r++, i++)
			{
				m_blocks[i].setActive(true);
				m_blocks[i].setGridPosition(5 + (c * m_blocks[i].getWidth()+2), 5 + ( r * 3 ));
			}
		}
		
		break;
	}

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
