/*
* Created By: Fraser Connolly
* Created Date: 2023-10-05
* 
* 2023-10-12 Separated out definitions from decelerations. 
*/

#include "Window.h"

Window::Window() : 
	m_hConsole( GetStdHandle ( STD_OUTPUT_HANDLE ) ), 
	m_width( 0 ), 
	m_height( 0 )
{
}

void Window::setWindow ( short width, short height )
{

	m_width = width;
	m_height = height;

	_COORD coord { m_width + 21 , m_height + 21 };

	if ( !SetConsoleScreenBufferSize ( m_hConsole, coord ) )
	{
		cout << "SetConsoleScreenBufferSize failed with error " << GetLastError ( ) << endl;
	}

	SMALL_RECT windowSize = { 10, 10, m_width + 20, m_height + 20 };
	if ( !SetConsoleWindowInfo ( m_hConsole, TRUE, &windowSize ) )
	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError ( ) << endl;
	}

	if ( !SetConsoleTitle ( L"Space Invaders" ) )
	{
		cout << "SetConsoleTitle failed with error " << GetLastError ( ) << endl;
	}

	HANDLE out = GetStdHandle ( STD_OUTPUT_HANDLE ); // this code hides the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo ( out, &cursorInfo );
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo ( out, &cursorInfo );
}

