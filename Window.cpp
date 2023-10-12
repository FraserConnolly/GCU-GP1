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

	_COORD coord{ m_width, m_height };

	if (!SetConsoleScreenBufferSize(hConsole, coord))
	{
		cout << "SetConsoleScreenBufferSize failed with error " << GetLastError() << endl;
	}

	SMALL_RECT windowSize = { 0, 0, m_width - 1, m_height - 1 };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}
}

