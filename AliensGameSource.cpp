#include "AliensGameSource.h"

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

	m_player.tick ( this );

	for ( Laser & laser : m_lasers )
	{
		laser.tick ( this );
	}

	for (Bomb& bomb : m_bombs)
	{
		bomb.tick(this);
	}

	setAlientPositions ( );
	setBarrierPositions ( );
}

void AliensGameSource::drawGame ( )
{
	// populate the back buffer
	const char * toBeDrawn = nullptr;

	// Draw Aliens
	for ( int a = 0; a < ALIENT_COUNT; a++ )
	{
		const Alien * alien = &m_aliens [ a ];
		toBeDrawn = alien->draw ( );

		for ( int i = 0; i < alien->getWidth ( ); i++ )
		{
			m_backBuffer->setChar ( alien->getGridX ( ) + i, alien->getGridY ( ), toBeDrawn [ i ] );
			m_backBuffer->setCharColour ( alien->getGridX ( ) + i, alien->getGridY ( ), ScreenBuffer::Colour::Fore_Red, ScreenBuffer::Colour::Back_Black );
		}
	}

	// alternative method to iterate through an array
	// remove before submission.
	/*for (const Alien& alien : m_aliens)
	{

	}*/

	// Draw barrier
	for ( int b = 0; b < BARRIER_COUNT; b++ )
	{
		Barrier * barrier = &m_barriers [ b ];
		toBeDrawn = barrier->draw ( );

		for ( int i = 0; i < barrier->getWidth ( ); i++ )
		{
			m_backBuffer->setChar ( barrier->getGridX ( ) + i, barrier->getGridY ( ), toBeDrawn [ i ] );
			m_backBuffer->setCharColour ( barrier->getGridX ( ) + i, barrier->getGridY ( ), ScreenBuffer::Colour::Fore_Cyan, ScreenBuffer::Colour::Back_Yellow );
		}
	}

	// Draw lasers
	for ( int l = 0; l < MAX_LASER_COUNT; l++ )
	{
		Laser * laser = &m_lasers [ l ];

		if ( !laser->getInFlight ( ) )
		{
			continue;
		}

		toBeDrawn = laser->draw ( );

		for ( int i = 0; i < laser->getWidth ( ); i++ )
		{
			m_backBuffer->setChar ( laser->getGridX ( ) + i, laser->getGridY ( ), toBeDrawn [ i ] );
			m_backBuffer->setCharColour ( laser->getGridX ( ) + i, laser->getGridY ( ), ScreenBuffer::Colour::Fore_Yellow, ScreenBuffer::Colour::Back_Black );
		}
	}

	// Draw bombs
	for ( int l = 0; l < MAX_LASER_COUNT; l++ )
	{
		Bomb * bomb = &m_bombs [ l ];

		if ( !bomb->getInFlight ( ) )
		{
			continue;
		}

		toBeDrawn = bomb->draw ( );

		for ( int i = 0; i < bomb->getWidth ( ); i++ )
		{
			m_backBuffer->setChar ( bomb->getGridX ( ) + i, bomb->getGridY ( ), toBeDrawn [ i ] );
			m_backBuffer->setCharColour ( bomb->getGridX ( ) + i, bomb->getGridY ( ), ScreenBuffer::Colour::Fore_Red, ScreenBuffer::Colour::Back_Black );
		}
	}

	// Draw player
	toBeDrawn = m_player.draw ( );

	for ( int i = 0; i < m_player.getWidth ( ); i++ )
	{
		m_backBuffer->setChar ( m_player.getGridX ( ) + i, m_player.getGridY ( ), toBeDrawn [ i ] );
	}

	// Draw ground
	toBeDrawn = m_ground.draw ( );

	for ( int i = 0; i < m_ground.getWidth ( ); i++ )
	{
		m_backBuffer->setChar ( m_ground.getGridX ( ) + i, m_ground.getGridY ( ), toBeDrawn [ i ] );
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

void AliensGameSource::setAlientPositions( )
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

		if (!laser->getInFlight())
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

		if ( ! bomb->getInFlight( ) )
		{
			return bomb;
		}
	}

	return nullptr;
}

