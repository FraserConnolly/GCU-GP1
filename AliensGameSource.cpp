#include "AliensGameSource.h"



void AliensGameSource::initaliseGame ( )
{
	GameSource::initaliseGame ( );

	for (int b = 0; b < BARRIER_COUNT; b++)
	{
		m_barriers[b].setGridPosition(b * 10, 35);
	}

	initaliseLevel();

	m_player.setGridPosition ( getScreenWidth( ) / 2, 40);

	m_ground.setGridPosition ( 0, 42 );

	m_scoreText.setGridPosition ( 5, 43 );

	m_keyboardInput.registerOnKey ( VK_SPACE,
									[ this ] ( WORD key, short status )
									{
										this->playMuisc ( );
									} );

	m_keyboardInput.registerKey ( VK_LEFT );
	m_keyboardInput.registerKey ( VK_RIGHT );
	m_keyboardInput.registerKey ( VK_RCONTROL );
}

void AliensGameSource::initaliseLevel()
{
	m_level++;

	Alien::resetGame( );
	
	m_lastAlienMoveTime = gameTime;
	m_alienMoveTimeout = Alien::getMovementTimeout();

	// reset alien positions
	for (size_t index = 0, row = 0; row < ALIEN_ROW_COUNT; row++)
	{
		for (size_t col = 0; col < ALIEN_COL_COUNT; col++, index++)
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

void AliensGameSource::updateGame()
{
	GameSource::updateGame ( );

	// check level over conditions

	if (!m_player.getActive())
	{
		// level over - lose
		GameSource::quit();
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

	// update game objects

	m_player.tick ( this );

	setAlienPositions ( );
	setBarrierPositions ( );

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
			m_player.setActive ( false );
		}
	}

}

void AliensGameSource::drawGame ( )
{
	// populate the back buffer
	pRenderCellData toBeDrawn = nullptr;

	// Draw Aliens
	GameSource::drawObjectsInArray ( m_aliens, ALIENT_COUNT );

	// Draw barrier
	GameSource::drawObjectsInArray ( m_barriers, BARRIER_COUNT );

	// Draw lasers
	GameSource::drawObjectsInArray ( m_lasers, MAX_LASER_COUNT );

	// Draw bombs
	GameSource::drawObjectsInArray ( m_bombs, MAX_BOMB_COUNT );

	// Draw player
	if ( m_player.getActive ( ) )
	{
		drawGameObject ( m_player );
	}

	// Draw ground
	if ( m_ground.getActive ( ) )
	{
		drawGameObject ( m_ground );
	}

	// Draw UI
	m_scoreText.updateText ( m_score );
	if ( m_scoreText.getActive ( ) )
	{
		drawGameObject ( m_scoreText );
	}

}

void AliensGameSource::playMuisc ( )
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

void AliensGameSource::setAlienPositions()
{
	if (m_lastAlienMoveTime > gameTime)
	{
		return;
	}

	int leftEdge = ALIEN_EDGE_PADDING;
	int rightEdge = getScreenWidth() - ALIEN_EDGE_PADDING;

	int leftX, rightX;

	Point translation ( 0, 0 );

	Alien::getEdgeAlienColumns(leftX, rightX);

	m_lastAlienMoveTime = gameTime + m_alienMoveTimeout;

	// update movement direction
	switch (m_previousMovement)
	{
	default:
	case AliensGameSource::DOWN:

		m_alienMoveTimeout = Alien::getMovementTimeout();
		// check which edge has been reached, and set the direction to be the opposite.
		m_previousMovement = (leftX <= leftEdge) ? AliensGameSource::RIGHT : AliensGameSource::LEFT;
		

		// stop us from going down repeatedly.
		leftX = getScreenWidth() / 2;
		rightX = leftX;
	case AliensGameSource::LEFT:
		if (leftX <= leftEdge)
		{
			// left edge reached
			m_previousMovement = AliensGameSource::DOWN;
			translation.X = 0;
			translation.Y = 1;
			break;
		}

 		translation.X = -1;
		translation.Y = 0;

		break;
	case AliensGameSource::RIGHT:
		if (rightX >= rightEdge)
		{
			// right edge reached
			m_previousMovement = AliensGameSource::DOWN;
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

void AliensGameSource::updateEdgeAlienPointers()
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

void AliensGameSource::setBarrierPositions ( )
{ 

}

Laser * const AliensGameSource::getAvilableLaser ( )
{
	for (int i = 0; i < MAX_LASER_COUNT; i++)
	{
		Laser * const laser = &m_lasers[i];

		if (!laser->getActive ())
		{
			return laser;
		}
	}

	return nullptr;
}

Bomb * const AliensGameSource::getAvilableBomb()
{
	for (int i = 0; i < MAX_LASER_COUNT; i++)
	{
		Bomb * const bomb = &m_bombs[ i ];

		if ( ! bomb->getActive ( ) )
		{
			return bomb;
		}
	}

	return nullptr;
}

