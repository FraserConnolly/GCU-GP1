#include "AliensGameSource.h"

void AliensGameSource::initaliseGame ( )
{
	GameSource::initaliseGame ( );

	for ( int a = 0; a < ALIENT_COUNT; a++ )
	{
		m_aliens [ a ].m_X = (a + 5) * 5;
		m_aliens [ a ].m_Y = 5;
	}

	for ( int b = 0; b < BARRIER_COUNT; b++ )
	{
		m_barriers [ b ].m_X = b * 10;
		m_barriers [ b ].m_Y = 20;
	}

	m_player.m_X = 10;
	m_player.m_Y = 30;

	m_ground.m_Y = 40;

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
	playerMoveTimer += deltaTime;
	if (playerMoveTimer > 0.5f)
	{
		playerMoveTimer = 0;
		m_player.m_X++;
		if (m_player.m_X >= 160)
		{
			m_player.m_X = 0;
		}
	}
}

void AliensGameSource::drawGame ( )
{
	// populate the back buffer
	drawGameObjects( );
	
	GameSource::drawGame( );
}

void AliensGameSource::drawGameObjects( )
{
	const char* toBeDrawn = nullptr;

	// Draw Aliens

	for ( int a = 0; a < ALIENT_COUNT; a++ )
	{
		const Alien * alien = &this->m_aliens [ a ];
		toBeDrawn = alien->draw();

		for (int i = 0; i < alien->getWidth(); i++)
		{
			m_backBuffer->setChar(alien->m_X + i, alien->m_Y, toBeDrawn[i]);
			m_backBuffer->setCharColour(alien->m_X + i, alien->m_Y, ScreenBuffer::Colour::Fore_Red, ScreenBuffer::Colour::Back_Black);
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
		Barrier * barrier = &this->m_barriers [ b ];
		toBeDrawn = barrier->draw();

		for (int i = 0; i < barrier->getWidth(); i++)
		{
			m_backBuffer->setChar(barrier->m_X + i, barrier->m_Y, toBeDrawn[i]);
			m_backBuffer->setCharColour(barrier->m_X + i, barrier->m_Y, ScreenBuffer::Colour::Fore_Cyan, ScreenBuffer::Colour::Back_Yellow );
		}
	}

	// Draw player

	toBeDrawn = m_player.draw();

	for (int i = 0; i < m_player.getWidth(); i++)
	{
		m_backBuffer->setChar(m_player.m_X + i, m_player.m_Y, toBeDrawn[i]);
	}

	// Draw ground

	toBeDrawn = m_ground.draw();

	for (int i = 0; i < m_ground.getWidth(); i++)
	{
		m_backBuffer->setChar(m_ground.m_X + i, m_ground.m_Y, toBeDrawn[i]);
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

