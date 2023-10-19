#include "AliensGameSource.h"

void AliensGameSource::drawGame()
{
	GameSource::drawGame();

	m_ground.draw(m_window.getWidth(), m_window.getHeight());
}

void AliensGameSource::setAlientPositions()
{
}

void AliensGameSource::setBarrierPositions()
{
}
