/*
* Created By: Fraser Connolly
* Created Date: 2023-10-12
*/

#pragma once
#include <iostream>
#include <string>
#include "Window.h"
#include "Ground.h"
#include "KeyboardInput.h"
#include "FrameTimer.h"
#include "MusicPlayer.h"

class GameSource
{
public:
	GameSource() { };

	void initaliseGame();
	void processInput();
	void updateGame();
	void drawGame();
	void gameLoop();
	void quit();
	void playMusic();

	KeyboardInput kInput = NULL;
	float deltaTime = 0;
	float deltaTimeSecond = 0;

private:
	bool m_runLoop = false;
	Window m_window;
	Ground m_ground;
	FrameTimer m_frameTimer;
	MusicPlayer m_musicPlayer;
};

