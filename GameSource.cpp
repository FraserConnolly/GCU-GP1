/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
*/

#pragma once
#include <iostream>
#include <string>
#include "Window.cpp"
#include "Ground.cpp"
#include "CharacterScreenRenderer.h"
#include "KeyboardInput.h"

class GameSource
{
public:
	GameSource() { };
	
	void initaliseGame()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		renderer = CharacterScreenRenderer(hOut, 160, 50);
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		kInput = KeyboardInput(hIn);
		m_window.setWindow(renderer.getWidth(), renderer.getHeight());
		m_ground = Ground(&renderer);
		m_runLoop = true;
	};

	void processInput()
	{
		kInput.tick();
	};

	void updateGame()
	{
		
	};

	void drawGame()
	{
		renderer.draw();
		m_ground.draw();
	};

	void quit()
	{
		m_runLoop = false;
	}

	int gameLoop()
	{
		if (!m_runLoop)
		{
			initaliseGame();
		}

		if (&renderer == NULL)
		{
			return 0x01;
		}

		if (&kInput == NULL)
		{
			return 0x02;
		}

		for (; m_runLoop == true ; )
		{
			processInput();
			updateGame();
			drawGame();
		}

		return 0;
	};
	
	CharacterScreenRenderer renderer = NULL;
	KeyboardInput kInput = NULL;

private:
	bool m_runLoop = false;
	Window m_window;
	Ground m_ground = NULL;
};

