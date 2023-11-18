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
	Window(HANDLE handle);
	~Window ( );

	void setWindow ( short width, short height );

	short getWidth ( ) const
	{
		return m_width;
	};

	short getHeight ( ) const
	{
		return m_height;
	};

private:
	HANDLE m_hConsole;
	short m_width;
	short m_height;

};

