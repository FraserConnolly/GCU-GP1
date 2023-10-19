/*
* Created By: Fraser Connolly
* Created Date: 2023-10-12
*/

#pragma once
#include <iostream>
#include <string>
#include "Window.h"
#include "Ground.h"
#include "FrameTimer.h"

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

	float deltaTime = 0;
	float deltaTimeSecond = 0;

private:
	bool m_runLoop = false;
	Window m_window;
	Ground m_ground;
	FrameTimer m_frameTimer;
};

