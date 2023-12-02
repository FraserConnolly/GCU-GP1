#include "AliensGameSource.h"

#define AlienHitScore 100

void AliensGameSource::initaliseGame ( )
{
	GameSource::initaliseGame ( );

	for ( int a = 0; a < ALIENT_COUNT; a++ )
	{
		m_aliens [ a ].setGridPosition ( ( a + 5 ) * 5, 5 );
	}

	for ( int b = 0; b < BARRIER_COUNT; b++ )
	{
		m_barriers [ b ].setGridPosition ( b * 10, 20 );
	}

	m_player.setGridPosition ( 10, 30 );

	m_ground.setGridPosition ( 0, 40 );

	m_scoreText.setGridPosition ( 5, 41 );

	m_keyboardInput.registerOnKey ( VK_SPACE,
									[ this ] ( WORD key, short status )
									{
										this->playMuisc ( );
									} );

	m_keyboardInput.registerKey ( VK_LEFT );
	m_keyboardInput.registerKey ( VK_RIGHT );
	m_keyboardInput.registerKey ( VK_RCONTROL );
}

void AliensGameSource::updateGame()
{
	GameSource::updateGame ( );

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
				
				// collision
				laser.onCollision ( alien, laser.getGridPosition ( ) );
				alien.onCollision ( laser, laser.getGridPosition ( ) );
				
				m_score += AlienHitScore;
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
				// collision
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

	// check level over conditions

	if ( ! m_player.getActive ( ) )
	{
		// level over - lose
		GameSource::quit ( );
	}

	bool allAliensDead = true;

	for ( Alien & alien : m_aliens )
	{
		if ( alien.getActive ( ) )
		{
			allAliensDead = false;
			break;
		}
	}

	if ( allAliensDead )
	{
		// level over - WIN
		GameSource::quit ( );
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

void AliensGameSource::setAlienPositions( )
{

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

