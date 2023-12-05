#include "Alien.h"

/// <summary>
/// This function returns the next timeout that the game should use for alien movement.
/// It also reduces the timeout that will be returned the next time this method is called.
/// Make sure to only call this methods when the aliens have moved or else the 
/// aliens will move more frequently than expected.
/// </summary>
/// <returns>The timeout before the next alien movement is allowed.</returns>

int Alien::getStartRow()
{
	return s_startRow;
}

void Alien::setStartRow(const int startRow)
{
	if (startRow < ALIEN_START_ROW_MIN)
	{
		s_startRow = ALIEN_START_ROW_MIN;
	}
	else if (startRow > ALIEN_START_ROW_MAX)
	{
		s_startRow = ALIEN_START_ROW_MAX;
	}
	else
	{
		s_startRow = startRow;
	}
}

void Alien::setEdgeAliens(const Alien* const leftAlien, const Alien* const rightAlien)
{
	s_leftMostAlien = leftAlien;
	s_rightMostAlien = rightAlien;
}

void Alien::getEdgeAlienColumns(int& leftColumn, int& rightColumn)
{
	if (s_leftMostAlien == nullptr || s_rightMostAlien == nullptr)
	{
		// This should never happen.
		throw;
	}

	leftColumn = s_leftMostAlien->getGridX();
	rightColumn = s_rightMostAlien->getGridX();
}

float Alien::getMovementTimeout()
{
	float timeout = ALIEN_MOVEMENT_TIMEOUT_MAX;

	timeout = timeout - (ALIEN_MOVEMENT_TIMEOUT_DECREMENT * s_timeoutCalls);

	if (timeout < ALIEN_MOVEMENT_TIMEOUT_MIN)
	{
		timeout = ALIEN_MOVEMENT_TIMEOUT_MIN;
	}

	s_timeoutCalls++;

	return timeout;
}

void Alien::resetGame()
{
	s_timeoutCalls = 0;
	s_startRow = ALIEN_START_ROW_MIN;
	s_leftMostAlien = nullptr;
	s_rightMostAlien = nullptr;
}

int Alien::s_startRow = ALIEN_START_ROW_MIN;
int Alien::s_timeoutCalls = 0;
const Alien* Alien::s_leftMostAlien = nullptr;
const Alien* Alien::s_rightMostAlien = nullptr;
