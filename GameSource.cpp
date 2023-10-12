/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
* 
* 2023-10-12 Seperated out implementation from header files.
*/

#include "GameSource.h"

void GameSource::initaliseGame()
{
	std::cout << "Game initalised" << std::endl;
	m_runLoop = true;
	m_window.setWindow(160, 50);
}

void GameSource::processInput()
{
	//std::cout << "Processing input" << '\n';
}

void GameSource::updateGame()
{
	//std::cout << "Update game" << '\n';
}

void GameSource::drawGame()
{
	system("cls");
	m_ground.draw(m_window.getWidth(), m_window.getHeight());
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
	}
}
