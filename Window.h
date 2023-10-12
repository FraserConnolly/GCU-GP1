/*
* Created By: Fraser Connolly
* Created Date: 2023-10-12
*/

#pragma once

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class Window
{
public:
	Window();

	void setWindow(short width, short height);
	short getWidth() { return m_width; };
	short getHeight() { return m_height; };

private:
	HANDLE hConsole = NULL;
	short m_width;
	short m_height;
};

