
/*
* Created By: Fraser Connolly
* Created Date: 2023-10-05
*/

#pragma once
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class Window
{
public:
	Window() : m_width(0), m_height(0)
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void setWindow(int width, int height) {

		this->m_width = width;
		this->m_height = height;

		_COORD coord;
		coord.X = width;
		coord.Y = height;

		if (!SetConsoleScreenBufferSize(hConsole, coord))
		{
			cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << endl;
		}

		SMALL_RECT windowSize = { 0, 0, width-1, height-1 };
		if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
		{
			cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
		}
	}


private:
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int m_width;
	int m_height;
};

