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

class GameSource
{
public:
	GameSource() { };

	virtual void initaliseGame();
	virtual void processInput();
	virtual void updateGame();
	virtual void drawGame();
	void gameLoop();
	void quit();

	float deltaTime = 0;
	float deltaTimeSecond = 0;
	
	KeyboardInput m_keyboardInput = NULL;

protected:

	// returns true if a non space character is drawn.
	bool drawChar(ostream& o, int * row, int * column) { };
	
	bool m_runLoop = false;
	Window m_window;
	FrameTimer m_frameTimer;
	MusicPlayer m_musicPlayer;

private:

	void quitKeyPressed(KEY_EVENT_RECORD ker);

};

