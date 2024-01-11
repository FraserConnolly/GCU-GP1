#include <random>
#include "SpaceInvaderMainScene.h"
#include "Resources.h"
#include "HighScoreScene.h"

void SpaceInvaderMainScene::initaliseGame ( int lastGameSceneResponse )
{
	GameScene::initaliseGame ( lastGameSceneResponse );
	setBarrierPositions ( );

	initaliseLevel();

	m_score = 0;

	m_player.setGridPosition ( getScreenWidth( ) / 2, PLAYER_ROW );
	m_player.setActive ( true );

	m_ground.setGridPosition ( 0, GROUND_ROW );

	m_scoreText.setGridPosition ( 5, SCORE_ROW );

	m_keyboardInput.registerOnKey ( VK_SPACE,
									[ this ] ( WORD key, short status )
									{
										this->playMuisc ( );
									} );

	m_keyboardInput.registerKey ( VK_LEFT );
	m_keyboardInput.registerKey ( VK_RIGHT );
	m_keyboardInput.registerKey ( VK_RCONTROL );
}

int SpaceInvaderMainScene::loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively )
{
	if ( getFrameCount ( ) > 0 )
	{
		// show score
		auto hs = std::make_shared<HighScoreScene> ( );

		hs->setScore ( m_score );
		hs->setGameLabel ( spaceInvadorsTextData, spaceInvadorsTextDataCols, asciiArtShadowRows, CellColour::Fore_Red );

		loadAdditively = true;
		newScene = hs;
		return 0;
	}

	return 0;
}

void SpaceInvaderMainScene::initaliseLevel()
{
	m_level++;

	Alien::resetGame( );
	
	m_nextAlienMoveTime = getGameTime();
	m_alienMoveTimeout = ALIEN_MOVEMENT_TIMEOUT_MAX;

	// reset alien positions
	for (int index = 0, row = 0; row < ALIEN_ROW_COUNT; row++)
	{
		for (int col = 0; col < ALIEN_COL_COUNT; col++, index++)
		{
			m_aliens[index].setGridPosition( 45 + ALIEN_EDGE_PADDING + (col * 10), Alien::getStartRow() + ( row * ALIEN_ROW_HEIGHT ) );
			m_aliens[index].setActive(true);
		}
	}

	// disable lasers and bombs
	for (Laser& laser : m_lasers)
	{
		laser.setActive(false);
	}

	for (Bomb& bomb : m_bombs)
	{
		bomb.setActive(false);
	}

	updateEdgeAlienPointers( );
}

void SpaceInvaderMainScene::updateGame()
{
	GameScene::updateGame ( );

	// check level over conditions

	if (!m_player.getActive())
	{
		// level over - lose
		GameScene::quit();
		return;
	}

	bool allAliensDead = true;

	for (Alien& alien : m_aliens)
	{
		if (alien.getActive())
		{
			allAliensDead = false;
			break;
		}
	}

	if (allAliensDead)
	{
		// level over - WIN
		initaliseLevel();
		return;
	}

	for ( Alien & alien : m_aliens )
	{
		if ( !alien.getActive ( ) )
		{
			continue;
		}

		if ( alien.getGridY ( ) + alien.getHeight( ) -1  >= ALIEN_GOAL_ROW )
		{
			// level over - lose
			// one of the aliens reached their goal line.
			GameScene::quit ( );
			return;
		}
	}

	// update game objects

	m_player.tick ( this );

	setAlienPositions ( );
	tryDropBomb( );

	for ( Laser & laser : m_lasers )
	{
		laser.tick ( this );
	}

	for (Bomb& bomb : m_bombs)
	{
		bomb.tick(this);
	}

	// check for collision 
	for ( Laser & laser : m_lasers )
	{
		bool hasCollided = false;

		if ( !laser.getActive( ) )
		{
			continue;
		}

		for ( Barrier & barrier : m_barriers )
		{
			if ( !barrier.getActive ( ) )
			{
				continue;
			}

			if ( laser.hasCollided ( barrier ) )
			{
				// collision
				laser.setActive ( false );
				barrier.setActive ( false );
				break;
			}
		}

		if ( !laser.getActive ( ) )
		{
			// There is no need to check for other collisions as the laser has been used.
			continue;
		}

		for ( Alien & alien : m_aliens )
		{
			if ( !alien.getActive ( ) )
			{
				continue;
			}

			if ( laser.hasCollided ( alien ) )
			{
				
				// collision between laser and alien
				laser.onCollision ( alien, laser.getGridPosition ( ) );
				alien.onCollision ( laser, laser.getGridPosition ( ) );

				// An alien has been killed to update the edge pointers 
				// in case it was an edge alien that was killed.
				updateEdgeAlienPointers( );
				
				m_score += ALIEN_HIT_SCORE;
				break;
			}

		}
	}

	for ( Bomb & bomb : m_bombs )
	{
		if ( !bomb.getActive ( ) )
		{
			continue;
		}

		for ( Barrier & barrier : m_barriers )
		{
			if ( !barrier.getActive ( ) )
			{
				continue;
			}

			if ( bomb.hasCollided ( barrier ) )
			{
				// collision between bomb and a barrier
				bomb.onCollision ( barrier, bomb.getGridPosition ( ) );
				barrier.onCollision ( bomb, bomb.getGridPosition ( ) );
				break;
			}
		}

		if ( bomb.hasCollided ( m_player ) )
		{
			bomb.onCollision ( m_player, bomb.getGridPosition ( ) );
			m_player.onCollision ( bomb, bomb.getGridPosition( ) );
		}

		if ( bomb.hasCollided ( m_ground ) )
		{
			bomb.onCollision ( m_ground, bomb.getGridPosition( ) );
		}
	}
	
	// Update UI
	m_scoreText.updateText ( m_score );

}

void SpaceInvaderMainScene::drawGame ( )
{
	// Draw barrier
	GameScene::drawObjectsInArray ( m_barriers, BARRIER_COUNT_MAX );

	// Draw Aliens
	GameScene::drawObjectsInArray ( m_aliens, ALIEN_COUNT );

	// Draw bombs
	GameScene::drawObjectsInArray ( m_bombs, BOMB_COUNT_MAX );

	// Draw lasers
	GameScene::drawObjectsInArray ( m_lasers, LASER_COUNT_MAX );

	// Draw ground
	drawGameObject ( m_ground );

	// Draw player
	drawGameObject ( m_player );

	// Draw UI
	drawGameObject ( m_scoreText );
}

void SpaceInvaderMainScene::playMuisc ( )
{
	// Declare the first few notes of the song, "Mary Had A Little Lamb".
	Note * Mary = new Note [ 13 ]
	{
		Note ( Tone::B, Duration::QUARTER ),
		Note ( Tone::A, Duration::QUARTER ),
		Note ( Tone::GbelowC, Duration::QUARTER ),
		Note ( Tone::A, Duration::QUARTER ),
		Note ( Tone::B, Duration::QUARTER ),
		Note ( Tone::B, Duration::QUARTER ),
		Note ( Tone::B, Duration::HALF ),
		Note ( Tone::A, Duration::QUARTER ),
		Note ( Tone::A, Duration::QUARTER ),
		Note ( Tone::A, Duration::HALF ),
		Note ( Tone::B, Duration::QUARTER ),
		Note ( Tone::D, Duration::QUARTER ),
		Note ( Tone::D, Duration::HALF )
	};

	// Play the song
	// note that the memory for Marry will be deallocated at the end of the playback.
	m_musicPlayer.Play ( Mary, 13 );
}

void SpaceInvaderMainScene::setAlienPositions()
{
	if (m_nextAlienMoveTime > getGameTime())
	{
		return;
	}

	int leftEdge = ALIEN_EDGE_PADDING;
	int rightEdge = getScreenWidth() - ALIEN_EDGE_PADDING;

	int leftX, rightX;

	Vector2Int translation ( 0, 0 );

	Alien::getEdgeAlienColumns(leftX, rightX);

	m_nextAlienMoveTime = getGameTime() + m_alienMoveTimeout;

	if (m_previousMovement == SpaceInvaderMainScene::DOWN)
	{
		m_alienMoveTimeout = Alien::getMovementTimeout();
		// check which edge has been reached, and set the direction to be the opposite.
		m_previousMovement = (leftX <= leftEdge) ? SpaceInvaderMainScene::RIGHT : SpaceInvaderMainScene::LEFT;
	}

	// update movement direction
	switch (m_previousMovement)
	{
	case SpaceInvaderMainScene::LEFT:
		if (leftX <= leftEdge)
		{
			// left edge reached
			m_previousMovement = SpaceInvaderMainScene::DOWN;
			translation.X = 0;
			translation.Y = 1;
			break;
		}

 		translation.X = -1;
		translation.Y = 0;

		break;
	case SpaceInvaderMainScene::RIGHT:
		if (rightX >= rightEdge)
		{
			// right edge reached
			m_previousMovement = SpaceInvaderMainScene::DOWN;
			translation.X = 0;
			translation.Y = 1;
			break;
		}

		translation.X = 1;
		translation.Y = 0;

		break;
	}

	translation.X *= ALIEN_X_TRANSLATION;
	translation.Y *= ALIEN_Y_TRANSLATION;

	// apply movement direction

	for (Alien& alien : m_aliens)
	{
		if (!alien.getActive())
		{
			continue;
		}

		alien.translateByGridUnit(translation.X, translation.Y);
	}
}

void SpaceInvaderMainScene::updateEdgeAlienPointers()
{
	int leftMostColumn = getScreenWidth();
	int rightMostColumn = 0;
	
	Alien const * left = nullptr;
	Alien const * right = nullptr;

	for (Alien& alien : m_aliens)
	{
		if (!alien.getActive())
		{
			continue;
		}

		int x = alien.getGridX();

		if ( x < leftMostColumn)
		{
			leftMostColumn = x;
			left = &alien;
		}

		if (x > rightMostColumn)
		{
			rightMostColumn = x;
			right = &alien;
		}
	}

	Alien::setEdgeAliens(left, right);
}

void SpaceInvaderMainScene::setBarrierPositions ( )
{ 
	int xOffset = BARRIER_BLOCK_EDGE_PADDING;
	for ( int b = 0; b < BARRIER_BLOCK_COUNT; b++ )
	{

		int row = 0;
		int rowSize = 1;

		for ( int i = 0; i < BARRIER_COUNT_PER_BLOCK; )
		{

			for ( int rb = 0; rb < rowSize; rb++, i++ )
			{
				Barrier & barrier = m_barriers [ ( b * BARRIER_COUNT_PER_BLOCK ) + i ];
				barrier.setGridPosition ( xOffset + ( ( rb - ( rowSize / 2 ) ) * BARRIER_CELL_WIDTH ), BARRIER_ROW + ( row * barrier.getHeight ( ) ) );
				barrier.setActive ( true );
			}

			row++;
			rowSize = ( ( row + 1 ) * 2 ) - 1;

			if ( BARRIER_COUNT_PER_BLOCK - i < rowSize )
			{
				// there aren't enough remaining blocks to make another row

				int largestRow = ( ( row ) * 2 ) - 1;

				// check to see if there enough blocks to add one to each existing row

				if ( BARRIER_COUNT_PER_BLOCK - i > row - 1 )
				{
					// return row size to its previous value (i.e. the largest row made)
					int rowsToExtend = row;

					for ( int re = 0; re < rowsToExtend ; re++, i++ )
					{
						rowSize = ( ( re + 1 ) * 2 ) - 1;

						Barrier & barrier = m_barriers [ ( b * BARRIER_COUNT_PER_BLOCK ) + i ];
						barrier.setGridPosition ( xOffset + ( ( rowSize - re ) * BARRIER_CELL_WIDTH ), BARRIER_ROW + ( re * BARRIER_CELL_HEIGHT ) );
						barrier.setActive ( true );
					}

					// allow for the extra block.
					largestRow++;
				}

				xOffset += ( largestRow * BARRIER_CELL_WIDTH ) + BARRIER_BLOCK_GAP;
				break;
			}
		}
	}
}

void SpaceInvaderMainScene::tryDropBomb()
{

	if (getGameTime() > m_nextAlienBomb)
	{
		auto bomb = getAvilableBomb();

		if (bomb == nullptr)
		{
			// no available bombs
			return;
		}

		// get a random alien to drop the bomb
		int randomIndex = static_cast<int>( ((double)rand() / RAND_MAX) * ALIEN_COUNT );

		// note that the alien at this index in the array may not be 
		// active so increment the random index until an alive alien is found.

		Alien* alien = nullptr;

		for ( int i = 0 ; i < ALIEN_COUNT ; i++ )
		{
			Alien & a = m_aliens[ randomIndex ];
			
			if ( a.getActive( ) )
			{
				alien = &a;
				break;
			}

			randomIndex++;
			randomIndex %= ALIEN_COUNT;
		}

		if (alien == nullptr)
		{
			// Failed to find an active alien. 
			// This shouldn't happen as the game should have finished before 
			// calling this method.
			return;
		}

		// spawn point for the bomb.
		Vector2Int startPosition = alien->getGridPosition();
		startPosition.X += 2;
		startPosition.Y += 2;

		bomb->launch(startPosition, BOMB_SPEED);

		// get a random delay between the minimum and maximum delay range.
		float bombTimeout = static_cast< float > (
			( ( float ) rand ( ) / RAND_MAX ) *
			( BOMB_DROP_TIMEOUT_MAX - BOMB_DROP_TIMEOUT_MIN ) + BOMB_DROP_TIMEOUT_MIN );

		m_nextAlienBomb = getGameTime() + bombTimeout;
	}

}

Laser * const SpaceInvaderMainScene::getAvilableLaser ( )
{
	for (int i = 0; i < LASER_COUNT_MAX; i++)
	{
		Laser * const laser = &m_lasers[i];

		if (!laser->getActive ())
		{
			return laser;
		}
	}

	return nullptr;
}

Bomb * const SpaceInvaderMainScene::getAvilableBomb()
{
	for (int i = 0; i < LASER_COUNT_MAX; i++)
	{
		Bomb * const bomb = &m_bombs[ i ];

		if ( ! bomb->getActive ( ) )
		{
			return bomb;
		}
	}

	return nullptr;
}

