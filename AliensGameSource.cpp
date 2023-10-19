#include "AliensGameSource.h"

void AliensGameSource::initaliseGame()
{
	for (int a = 0; a < ALIENT_COUNT; a++)
	{
		Alien * alien = &this->m_aliens[a];
		alien->m_X = a * 2;
		alien->m_Y = 0;
	}

	for (int b = 0; b < BARRIER_COUNT; b++)
	{
		Barrier * barrier = &this->m_barriers[b];
		barrier->m_X = b * 10;
		barrier->m_Y = 20;
	}

	this->m_player.m_X = 40;
	this->m_player.m_Y = 40;

	this->m_ground.m_Y = 49;

	GameSource::initaliseGame();
}

void AliensGameSource::drawGame()
{
	GameSource::drawGame();

	for (int row = 0; row < m_window.getHeight() ; row++)
	{
		bool drawnToScreen = false;

		for (int column = 0; column < m_window.getWidth() ; )
		{
			drawnToScreen = drawChar( std::cout , row, column);
		}

		std::cout << std::endl;
	}
}

bool AliensGameSource::drawChar(ostream& o, int& row, int& column)
{
	// Draw Aliens

	for (int a = 0; a < ALIENT_COUNT; a++)
	{
		Alien * alien = &this->m_aliens[a];
		if (alien->inPosition(column, row))
		{
			o << alien->draw();
			column += alien->getWidth();
			return true;
		}
	}

	// Draw barrier

	for (int b = 0; b < BARRIER_COUNT; b++)
	{
		Barrier * barrier = &this->m_barriers[b];
		if (barrier->inPosition(column, row))
		{
			o << barrier->draw();
			column += barrier->getWidth();
			return true;
		}
	}

	// Draw player

	if (this->m_player.inPosition(column, row))
	{
		o << this->m_player.draw();
		column += this->m_player.getWidth();
		return true;
	}

	// Draw ground

	if (this->m_ground.inPosition(column, row))
	{
		o << this->m_ground.draw();
		column += this->m_ground.getWidth();
		return true;
	}

	// nothing drawn so lets draw a space character

	o << ' ';
	column += 1;
	
	return false;
}

void AliensGameSource::setAlientPositions()
{
}

void AliensGameSource::setBarrierPositions()
{
}
