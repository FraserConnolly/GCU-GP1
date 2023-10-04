/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
*/

#pragma once
#include <iostream>
#include <string>
#include "CharacterScreenRenderer.h"
#include "KeyboardInput.h"

class GameSource
{
public:
	GameSource()
	{ 
		initaliseGame();
	};

	void initaliseGame()
	{
		std::cout << "Game initialised" << '\n';
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		renderer = CharacterScreenRenderer(hOut);
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		kInput = KeyboardInput(hIn);
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
	};

	void quit()
	{
		m_runLoop = false;
	}

	int gameLoop()
	{

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
	
	KeyboardInput kInput = NULL;
	CharacterScreenRenderer renderer = NULL;

private:
	int m_width, m_height;
	bool m_runLoop = true;
};

