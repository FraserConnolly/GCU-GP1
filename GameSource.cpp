/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
*/

#pragma once
#include <iostream>
#include <string>
#include "Window.cpp"
#include "Ground.cpp"

class GameSource
{
public:
	GameSource() { };
	
	void initaliseGame()
	{
		std::cout << "Game initalised" << std::endl;
		m_runLoop = true;
		m_window.setWindow(160, 50);
	};

	void processInput()
	{
		//std::cout << "Processing input" << '\n';
	};

	void updateGame()
	{
		//std::cout << "Update game" << '\n';
	};

	void drawGame()
	{
		system("cls");
		m_ground.draw(160, 50);
	};

	void gameLoop()
	{
		if (!m_runLoop)
		{
			initaliseGame();
		}

		for (; m_runLoop == true ; )
		{
			processInput();
			updateGame();
			drawGame();
		}
	};

private:
	bool m_runLoop = false;
	Window m_window;
	Ground m_ground;
};

