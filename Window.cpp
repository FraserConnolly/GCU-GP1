/*
* Created By: Fraser Connolly
* Created Date: 2023-10-05
* 
* 2023-10-12 Seperated out definitions from declerations. 
*/

#include "Window.h"

Window::Window()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	this->m_width = 0;
	this->m_height = 0;
}

void Window::setWindow(short width, short height) {

	this->m_width = width;
	this->m_height = height;

	_COORD coord{ m_width + 21 , m_height + 21 };

	if (!SetConsoleScreenBufferSize(hConsole, coord))
	{
		cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << endl;
	}

	SMALL_RECT windowSize = { 10, 10, width + 20, height + 20 };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}

	if (!SetConsoleTitle(L"Space Invaders"))
	{
		cout << "SetConsoleTitle failed with error " << GetLastError() << endl;
	}

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // this code hides the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

