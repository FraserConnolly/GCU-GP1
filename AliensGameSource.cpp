#include "AliensGameSource.h"

void AliensGameSource::initaliseGame ( )
{
	GameSource::initaliseGame ( );

	for ( int a = 0; a < ALIENT_COUNT; a++ )
	{
		m_aliens [ a ].m_X = a * 2;
		m_aliens [ a ].m_Y = 0;
	}

	for ( int b = 0; b < BARRIER_COUNT; b++ )
	{
		m_barriers [ b ].m_X = b * 10;
		m_barriers [ b ].m_Y = 20;
	}

	m_player.m_X = 40;
	m_player.m_Y = 40;

	m_ground.m_Y = 49;

	m_keyboardInput.registerOnKey ( VK_SPACE,
									[ this ] ( KEY_EVENT_RECORD ker )
									{
										this->playMuisc ( ker );
									} );
}

void AliensGameSource::drawGame ( )
{
	GameSource::drawGame ( );

	for ( int row = 0; row < m_window.getHeight ( ) ; row++ )
	{
		bool drawnToScreen = false;

		for ( int column = 0; column < m_window.getWidth ( ) ; )
		{
			drawnToScreen = drawChar ( std::cout, row, column );
		}

		std::cout << std::endl;
	}
}

bool AliensGameSource::drawChar ( ostream & o, int & row, int & column )
{
	// Draw Aliens

	for ( int a = 0; a < ALIENT_COUNT; a++ )
	{
		Alien * alien = &this->m_aliens [ a ];
		if ( alien->inPosition ( column, row ) )
		{
			o << alien->draw ( );
			column += alien->getWidth ( );
			return true;
		}
	}

	// Draw barrier

	for ( int b = 0; b < BARRIER_COUNT; b++ )
	{
		Barrier * barrier = &this->m_barriers [ b ];
		if ( barrier->inPosition ( column, row ) )
		{
			o << barrier->draw ( );
			column += barrier->getWidth ( );
			return true;
		}
	}

	// Draw player

	if ( m_player.inPosition ( column, row ) )
	{
		o << m_player.draw ( );
		column += m_player.getWidth ( );
		return true;
	}

	// Draw ground

	if ( m_ground.inPosition ( column, row ) )
	{
		o << m_ground.draw ( );
		column += m_ground.getWidth ( );
		return true;
	}

	// nothing drawn so lets draw a space character

	o << ' ';
	column += 1;

	return false;
}

void AliensGameSource::playMuisc ( KEY_EVENT_RECORD ker )
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

