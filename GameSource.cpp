/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
* 
* 2023-10-12 Seperated out implementation from header files.
*/

#include "GameSource.h"

void GameSource::initaliseGame()
{
	deltaTime = 0;
	m_frameTimer.start();
	m_window.setWindow(160, 50);
	m_runLoop = true;
	std::cout << "Game initalised" << std::endl;
}

void GameSource::processInput()
{
}

void GameSource::updateGame()
{
}

void GameSource::drawGame()
{
	system("cls");
}

void GameSource::gameLoop()
{
	if (!m_runLoop)
	{
		initaliseGame();
	}

	for (; m_runLoop == true; )
	{
		processInput();
		updateGame();
		drawGame();
		m_frameTimer.restart();
		deltaTime = m_frameTimer.elapsedMilliseconds();
		deltaTimeSecond = m_frameTimer.elapsedSeconds();
	}
};

void GameSource::quit()
{
	this -> m_runLoop = false;
}
