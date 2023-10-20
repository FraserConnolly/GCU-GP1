/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
* 
* 2023-10-12 Separated out implementation from header files.
*/

#include "GameSource.h"

void GameSource::initaliseGame()
{
	deltaTime = 0;
	m_frameTimer.start();
	m_window.setWindow(160, 50);
	m_runLoop = true;
	
	m_keyboardInput = KeyboardInput(GetStdHandle(STD_INPUT_HANDLE));
	m_keyboardInput.registerOnKey(VK_ESCAPE, 
		[this](KEY_EVENT_RECORD ker) {
			this->quitKeyPressed(ker);
		} );

	std::cout << "Game initialised" << std::endl;
}

void GameSource::processInput()
{
	m_keyboardInput.tick();
}

void GameSource::updateGame()
{
	m_musicPlayer.tick(deltaTime);
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

void GameSource::quitKeyPressed(KEY_EVENT_RECORD ker)
{
	if (!ker.bKeyDown)
	{
		return;
	}

	quit();
}
