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
#include "Ground.h"
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
	virtual void processInput ( );
	virtual void updateGame ( );
	virtual void drawGame ( );
	void gameLoop ( );
	void quit ( );

	KeyboardInput m_keyboardInput;

	float deltaTimeMs = 0;
	float deltaTime   = 0;
	float gameTime    = 0;

	KeyboardInput m_keyboardInput = nullptr;

protected:

	// returns true if a non space character is drawn.
	bool drawChar ( ostream & o, int * row, int * column )
	{ };

	bool m_runLoop = false;
	FrameTimer m_frameTimer;
	MusicPlayer m_musicPlayer;
	
	/// <summary>
	/// This screen buffer pointed to by m_backBuffer 
	/// will never be the active console buffer.
	/// </summary>
	ScreenBuffer* m_backBuffer = nullptr;

private:

	void quitKeyPressed ( );
	ScreenBuffer* m_frontBuffer = nullptr;
	Window m_stdWindow;

};

