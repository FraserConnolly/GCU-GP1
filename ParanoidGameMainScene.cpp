#include "ParanoidGameMainScene.h"
#include "HighScoreScene.h"
#include "Resources.h"

void ParanoidGameMainScene::initaliseGame( int lastGameSceneResponse )
{

	GameScene::initaliseGame( lastGameSceneResponse );

	initaliseLevel();

	m_paddle.setGridPosition(getScreenWidth() / 2, 40);

	m_ground.setGridPosition(0, 42);

	m_scoreText.setGridPosition(5, 43);

	m_keyboardInput.registerKey(VK_SPACE);
	m_keyboardInput.registerKey(VK_LEFT);
	m_keyboardInput.registerKey(VK_RIGHT);

	m_score = 0;
	m_level = 0;
}

void ParanoidGameMainScene::updateGame ( )
{ 
	GameScene::updateGame ( );

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
			GameScene::quit();
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
			m_level++;
			m_score += 1'000;
			initaliseLevel();
			return;
		}
	}

	m_paddle.tick(this);

	for (Ball& ball : m_balls)
	{
		ball.tick(this);
	}
	
	for ( PowerUp & powerUp : m_powerUps )
	{
		powerUp.tick ( this );
	}

	// check for collisions

	for (Ball& ball : m_balls)
	{
		if ( !ball.getActive( ) )
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
				tryLaunchPowerUp ( ball.getGridPosition ( ) );
				m_score += 10;

				if (!block.getActive())
				{
					// add an additional 20 points for destroying a block
					m_score += 20;
				}
				break;
			}
		}

		// re-check if the ball is active as it may have been deactivated by a collision with a block.

		if ( !ball.getActive( ) )
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

		if ( powerUp.hasCollided ( m_paddle ) )
		{
			powerUp.onCollision ( m_paddle, powerUp.getGridPosition ( ) );
			m_score += 15;

			if ( powerUp.getPowerUp ( ) == POWER_UP_TYPE::BALL_MULTIPLY )
			{
				Ball * activeBalls [ BALL_COUNT_MAX ] ;

				for ( size_t i = 0; i < BALL_COUNT_MAX; i++ )
				{
					activeBalls [ i ] = nullptr;
				}

				int activeBallIndex = 0;

				// fill the active balls array with pointers to active balls.
				for ( Ball & ball : m_balls )
				{
					if ( !ball.getActive ( ) )
					{
						continue;
					}

					activeBalls [ activeBallIndex++ ] = &ball;
				}

				// iterate over the active balls array to create new balls at their position.
				for ( size_t i = 0; i < activeBallIndex; i++ )
				{
					Ball * newBall = getAvilableBall ( );

					if ( newBall == nullptr )
					{
						break;
					}

					Ball * ball = activeBalls [ i ];
					Vector2 direction = ball->getDirection ( );
					newBall->setDirection ( direction );

					// get a random new angle between -15 and 15 degrees
					float newAngle = ( float ) (
						( ( float ) rand ( ) / RAND_MAX ) * 30 ) - 15;

					// turn the ball 90 degree left or right relative to the original ball at random.
					newAngle += ( rand ( ) > RAND_MAX / 2 ) ? 90 : -90;

					newBall->rotate ( newAngle );
					newBall->launch ( ball->getGridPosition ( ), BALL_STARTING_SPEED );
				}
			}
			else
			{
				m_paddle.applyPowerUp ( powerUp.getPowerUp ( ), this );

				for ( Ball & ball : m_balls )
				{
					ball.applyPowerUp ( powerUp.getPowerUp ( ), this );
				}
			}
		}
	}

	m_scoreText.updateText(m_score);
	//m_frameCountText.updateText(1/getDeltaTime());
	//m_ballDirectionText.updateText ( m_balls [ 0 ].getDirection().X, m_balls [ 0 ].getDirection ( ).Y );
	//m_ballGridPositionText.updateText ( m_balls [ 0 ].getGridX ( ), m_balls [ 0 ].getGridY ( ) );

}

void ParanoidGameMainScene::drawGame()
{
	// populate the back buffer
	pRenderCellData toBeDrawn = nullptr;

	// Draw player
	drawGameObject(m_paddle);

	// Draw ground
	drawGameObject(m_ground);

	// Draw blocks
	GameScene::drawObjectsInArray(m_blocks, BLOCK_MAX_COUNT);

	// Draw balls
	GameScene::drawObjectsInArray(m_balls, BALL_COUNT_MAX);

	// Draw power ups
	GameScene::drawObjectsInArray(m_powerUps, POWER_UP_MAX_COUNT);

	// Draw UI
	drawGameObject(m_scoreText);
}

int ParanoidGameMainScene::loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively )
{
	if ( getFrameCount ( ) > 0 )
	{
		// show score
		auto hs = std::make_shared<HighScoreScene> ( );
	
		hs->setScore ( m_score );
		hs->setGameLabel ( paranoidTextData, paranoidTextDataCols, asciiArtShadowRows, CellColour::Fore_Green );

		loadAdditively = true;
		newScene = hs;
		return 0;
	}

	return 0;
}

void ParanoidGameMainScene::startLevel()
{
	if (getHasStarted())
	{
		// can not start a level which has already started
		return;
	}

	m_levelStartTime = getGameTime();

	Ball* firstBall = getAvilableBall();

	if (firstBall == nullptr)
	{
		throw;
	}

	// set the direction to at a 45 degree angle from the paddle.
	Vector2 direction ( 1, -1 );
	direction.normalise ( );
	firstBall->setDirection(direction);
	
	// launch the ball from above the center of the paddle
	firstBall->launch(
		Vector2Int(m_paddle.getGridX() + (m_paddle.getWidth() / 2),
			m_paddle.getGridY() - 1),
		BALL_STARTING_SPEED
	);
}

Ball* const ParanoidGameMainScene::getAvilableBall()
{
	for (int i = 0; i < BALL_COUNT_MAX; i++)
	{
		Ball* const ball = &m_balls[i];

		if (!ball->getActive())
		{
			return ball;
		}
	}

	return nullptr;
}

PowerUp* const ParanoidGameMainScene::getAvilablePowerUp()
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

void ParanoidGameMainScene::initaliseLevel ( )
{
	// set the position of each block depending on which level is loading.
	int levelIndex = m_level % 3; // 3 == number of playable levels
	CellColour colour;

	switch ( levelIndex )
	{
		default:
		case 0:
		{
			for ( int i = 0, c = 0; c < 15; c++ )
			{
				for ( int r = 0; r < 5; r++, i++ )
				{
					m_blocks [ i ].setGridPosition ( 20 + ( c * m_blocks [ i ].getWidth ( ) + 1 ), 4 + ( r * ( m_blocks [ i ].getHeight ( ) + 3 ) ) );

					switch ( r % 5 )
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

					m_blocks [ i ].setColour ( colour );
					m_blocks [ i ].setDamage ( 0 );
					m_blocks [ i ].setActive ( true );
				}
			}

			break;
		}
		case 1:
		{
			int x, y, sectionIndex;
			sectionIndex = 0;
			x = 0;

			for ( int i = 0, c = 0; c < 12; c++ )
			{
				if ( c % 3 == 0 )
				{
					x += 10;
				}

				y = 0;

				for ( int r = 0; r < 6; r++, i++ )
				{

					if ( !( r % 2 ) )
					{
						y += 3;
					}

					if ( i % 6 == 0 )
					{
						sectionIndex++;
					}

					m_blocks [ i ].setGridPosition ( 5 + ( c * m_blocks [ i ].getWidth ( ) + 2 ) + x, 2 + ( r * ( m_blocks [ i ].getHeight ( ) ) ) + y );

					switch ( sectionIndex % 7 )
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

					m_blocks [ i ].setColour ( colour );
					m_blocks [ i ].setDamage ( 0 );
					m_blocks [ i ].setActive ( true );
				}
			}

			break;
		}
		case 2:
		{
			for ( int i = 0, c = 0; c < 15; c++ )
			{
				for ( int r = 0; r < 5; r++, i++ )
				{
					if ( c < 8 )
					{
						m_blocks [ i ].setGridPosition ( 10 + ( c * m_blocks [ i ].getWidth ( ) ), 5 + ( r * m_blocks [ i ].getHeight ( ) ) );
					}
					else
					{
						m_blocks [ i ].setGridPosition ( 30 + ( c * m_blocks [ i ].getWidth ( ) ), 5 + ( r * m_blocks [ i ].getHeight ( ) ) );
					}

					switch ( i % 6 )
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

					m_blocks [ i ].setDamage ( 0 );
					m_blocks [ i ].setColour ( colour );
					m_blocks [ i ].setActive ( true );
				}
			}

			break;
		}
		case 3: // test level - not in release game
		{
			for ( int i = 0, c = 0; c < 1; c++ )
			{
				m_blocks [ i ].setGridPosition ( 50 + ( c * m_blocks [ i ].getWidth ( ) + 2 ), 30 + ( ( m_blocks [ i ].getHeight ( ) ) ) );
				m_blocks [ i ].setColour ( Fore_Yellow );
				m_blocks [ i ].setDamage ( 2 );
				m_blocks [ i ].setActive ( true );
			}

			break;
		}
	}

	// disable all balls and power ups
	for ( Ball & ball : m_balls )
	{
		ball.resetPowerUps ( );
		ball.setActive ( false );
	}

	for ( PowerUp & powerUps : m_powerUps )
	{
		powerUps.setActive ( false );
	}

	m_paddle.resetPowerUps ( );
	m_levelStartTime = 0;
}

void ParanoidGameMainScene::tryLaunchPowerUp ( const Vector2Int & launchPoint )
{ 
	PowerUp * powerUp = getAvilablePowerUp ( );

	if ( powerUp == nullptr )
	{
		// no available power ups.
		return;
	}

	int randomPowerUp = static_cast<int> ( 
		( static_cast<double> ( rand ( ) ) / RAND_MAX ) * static_cast<int> ( POWER_UP_TYPE::POWER_UP_COUNT ) );

	powerUp->setPowerUp ( ( POWER_UP_TYPE ) randomPowerUp );
	powerUp->launch ( launchPoint, POWER_UP_SPEED );
}
