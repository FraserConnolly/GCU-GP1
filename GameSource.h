/*
* Created By: Fraser Connolly
* Created Date: 2023-10-12
* 
* 2023-10-19 Moved Aliens game code to its own derived class.
*/

#pragma once
#include <iostream>
#include <string>
#include "Window.h"
#include "FrameTimer.h"
#include "KeyboardInput.h"
#include "MusicPlayer.h"
#include "ScreenBuffer.h"

class GameSource
{
public:
	GameSource()
		: m_stdWindow(GetStdHandle(STD_OUTPUT_HANDLE))
	{ };

	~GameSource()
	{
		delete m_backBuffer;
		delete m_frontBuffer;

		// restore the screen buffer to the standard output.
		SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	}

	virtual void initaliseGame ( );
	void gameLoop ( );
	void quit ( );

	KeyboardInput m_keyboardInput;

	/// <summary>
	/// The length of time in seconds that the game has been running for.
	/// </summary>
	float gameTime = 0;

	/// <summary>
	/// The length of time in seconds that the previous frame took to be completed.
	/// </summary>
	float deltaTime = 0;

	/// <summary>
	/// The length of time in milliseconds that the previous frame took to be completed.
	/// </summary>
	float deltaTimeMs = 0;

	inline const int getScreenWidth ( ) const
	{
		return m_stdWindow.getWidth ( );
	}

	inline const int getScreenHeight ( ) const
	{
		return m_stdWindow.getHeight ( );
	}

protected:
	
	virtual void processInput ( );
	virtual void updateGame ( );
	virtual void drawGame ( ) = 0;

	bool m_runLoop = false;
	FrameTimer m_frameTimer;
	MusicPlayer m_musicPlayer;

	/// <summary>
	/// This screen buffer pointed to by m_backBuffer 
	/// will never be the active console buffer.
	/// </summary>
	ScreenBuffer* m_backBuffer = nullptr;

private:
	
	void renderFrame ( );
	void quitKeyPressed ( );
	
	ScreenBuffer* m_frontBuffer = nullptr;
	Window m_stdWindow;
};

