/*
* Created By: Fraser Connolly
* Created Date: 2023-10-05
* 
* 2023-10-12 Separated out definitions from decelerations. 
*/

#include "Window.h"

Window::Window(HANDLE handle) : 
	m_hConsole( handle ), 
	m_width( 0 ), 
	m_height( 0 )
{
}

Window::~Window()
{
	// this code restores the cursor
	// note to self this should really restore the curosr to however it was before running this game.
	// at the moment it is assuiming that cursor was visible.

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(m_hConsole, &cursorInfo);
	cursorInfo.bVisible = true; 
	SetConsoleCursorInfo(m_hConsole, &cursorInfo);
}

void Window::setWindow ( short width, short height )
{

	m_width = width;
	m_height = height;

	CONSOLE_SCREEN_BUFFER_INFO info;

	GetConsoleScreenBufferInfo(m_hConsole, &info);

	_COORD coord = info.dwSize;

	if (coord.X < width)
	{
		coord.X = width;
	}

	if (coord.Y < height)
	{
		coord.Y = height;
	}

	if ( !SetConsoleScreenBufferSize ( m_hConsole, coord ) )
	{
		cout << "SetConsoleScreenBufferSize failed with error " << GetLastError ( ) << endl;
	}

	SMALL_RECT windowSize = { 0, 0, coord.X -1 , coord.Y - 1};

	if ( !SetConsoleWindowInfo ( m_hConsole, TRUE, &windowSize ) )
	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError ( ) << endl;
	}

	if ( !SetConsoleTitle ( L"Space Invaders" ) )
	{
		cout << "SetConsoleTitle failed with error " << GetLastError ( ) << endl;
	}

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo ( m_hConsole, &cursorInfo );
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo ( m_hConsole, &cursorInfo );
}


