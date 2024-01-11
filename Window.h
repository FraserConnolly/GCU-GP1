#pragma once

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class Window
{
public:
	Window(HANDLE handle);
	Window(const Window& other); // copy constructor
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

