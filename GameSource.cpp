/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
* 
* 2023-10-12 Separated out implementation from header files.
*/

#define PrintDebugRulers

#include "GameSource.h"
#include "GameObject.h"

void GameSource::initaliseGame ( )
{
	m_deltaTimeMs = 0;
	m_frameTimer.start ( );
	
	m_stdWindow.setWindow(160, 50);

	m_frontBuffer = new ScreenBuffer(160, 50);
	m_backBuffer  = new ScreenBuffer(160, 50);
	
	m_runLoop = true;
	
	m_keyboardInput = KeyboardInput ( GetStdHandle ( STD_INPUT_HANDLE ) );
	m_keyboardInput.registerOnKey ( VK_ESCAPE,
									[ this ] ( WORD key, short status )
									{
										this->quitKeyPressed ( );
									} );

	std::cout << "Game initialised" << std::endl;
}

void GameSource::processInput ( )
{
	m_keyboardInput.tick ( m_deltaTime );
}

void GameSource::updateGame ( )
{
	m_musicPlayer.tick ( m_deltaTimeMs );
}

/// <summary>
/// Helper method that draws a GameObject to the back buffer.
/// </summary>
/// <param name="object">The object to draw.</param>
void GameSource::drawGameObject ( const GameObject & object )
{
	if (!object.getActive())
	{
		// don't draw non-active objects.
		return;
	}

	m_backBuffer->applyRenderData ( object.getGridX ( ), object.getGridY ( ),
									object.getWidth ( ), object.getHeight ( ),
									object.draw ( ) );
}

void GameSource::renderFrame ( )
{
	// swap front and back buffer
	auto buffer = m_frontBuffer;
	m_frontBuffer = m_backBuffer;
	m_backBuffer = buffer;

#ifdef PrintDebugRulers

	// Draw Debug rows
	for (int i = 0; i < 50; i++)
	{
		char buffer[4];

		sprintf_s(buffer, "%03d", i);

		m_backBuffer->setCharColour(0, i, CellColour::Fore_Black, CellColour::Back_White);
		m_backBuffer->setChar(0, i, buffer[0]);
		m_backBuffer->setChar(1, i, buffer[1]);
		m_backBuffer->setChar(2, i, buffer[2]);

		m_backBuffer->setCharColour(getScreenWidth() - 1, i, CellColour::Fore_Black, CellColour::Back_White);
		m_backBuffer->setChar(getScreenWidth() - 3, i, buffer[0]);
		m_backBuffer->setChar(getScreenWidth() - 2, i, buffer[1]);
		m_backBuffer->setChar(getScreenWidth() - 1, i, buffer[2]);
	}

	for (int i = 0; i < 160; i++)
	{
		m_backBuffer->setCharColour(i, 0, CellColour::Fore_Black, CellColour::Back_White);
		m_backBuffer->setCharColour(i, getScreenHeight()-1, CellColour::Fore_Black, CellColour::Back_White);

		if (i % 10 != 0)
		{
			continue;
		}

		char buffer[4];

		sprintf_s(buffer, "%03d", i);

		m_backBuffer->setChar(i, 0, buffer[0]);
		m_backBuffer->setChar(i + 1, 0, buffer[1]);
		m_backBuffer->setChar(i + 2, 0, buffer[2]);

		m_backBuffer->setChar(i,     getScreenHeight() - 1, buffer[0]);
		m_backBuffer->setChar(i + 1, getScreenHeight() - 1, buffer[1]);
		m_backBuffer->setChar(i + 2, getScreenHeight() - 1, buffer[2]);
	}

#endif

	// render the back buffer to the screen.
	m_frontBuffer->displayBuffer();
}

void GameSource::gameLoop ( )
{
	if ( !m_runLoop )
	{
		initaliseGame ( );
	}

	for ( ; m_runLoop == true; )
	{
		processInput ( );
		updateGame ( );
		drawGame ( );
		renderFrame ( );
		m_frameTimer.restart ( );
		m_deltaTimeMs = m_frameTimer.elapsedMilliseconds ( );
		m_deltaTime = m_frameTimer.elapsedSeconds ( );
		m_gameTime += m_deltaTime;
		m_frameCount++;
	}
}

void GameSource::quit ( )
{
	m_runLoop = false;
}

void GameSource::quitKeyPressed ( )
{
	quit ( );
}
