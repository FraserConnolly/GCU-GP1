/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
*/

#pragma once
#include <iostream>
#include <string>

class GameSource
{
public:
	GameSource() { };
	
	void initaliseGame()
	{
		std::cout << "Game initalised" << '\n';
	};

	void processInput()
	{
		std::cout << "Processing input" << '\n';
	};

	void updateGame()
	{
		std::cout << "Update game" << '\n';
	};

	void drawGame()
	{
		std::cout << "Draw game" << '\n';
	};

	void gameLoop()
	{
		initaliseGame();

		for (; m_runLoop == true ; )
		{
			processInput();
			updateGame();
			drawGame();
		}
	};

private:
	int m_width, m_height;
	bool m_runLoop = true;

};

