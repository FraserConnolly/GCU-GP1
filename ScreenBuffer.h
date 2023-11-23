#pragma once
#include "Window.h"


// note that in Lab 8 Bryan Young has this declared as a stuct.
class ScreenBuffer
{
public:
	
	enum Colour
	{
		Fore_Black = 0x0000,
		Fore_Blue = 0x0001,
		Fore_Green = 0x0002,
		Fore_Red = 0x0004,
		Fore_White = 0x0007,

		Fore_Cyan    = Fore_Blue | Fore_Green,
		Fore_Magenta = Fore_Blue | Fore_Red,
		Fore_Yellow  = Fore_Red  | Fore_Green,

		Back_Black = 0x0000,
		Back_Blue = 0x0010,
		Back_Green = 0x0020,
		Back_Red   = 0x0040,
		Back_White = 0x0070,

		Back_Cyan    = Back_Blue | Back_Green,
		Back_Magenta = Back_Blue | Back_Red,
		Back_Yellow  = Back_Red  | Back_Green,
	};

	ScreenBuffer(const int x, const int y);

	ScreenBuffer(const ScreenBuffer& other );		// Copy constructor
	ScreenBuffer(ScreenBuffer&& other) noexcept;	// Move constructor

	ScreenBuffer& operator=(const ScreenBuffer& other);		// Copy Assignment Operator
	ScreenBuffer& operator=(ScreenBuffer&& other) noexcept;	// Move Assignment Operator

	~ScreenBuffer();

	char getChar(const int x, const int y) const;
	void setChar(const int x, const int y, char c);
	void setCharColour(const int x, const int y, Colour foreground, Colour background);
	void setBackgroundColour(Colour background);
	void setForegroundColour(Colour foreground);


	/// <summary>
	/// Sets all characters in the buffer to the space character i.e. ' '.
	/// </summary>
	void clearBuffer();

	/// <summary>
	/// Copies the contents of the local buffer to the output buffer
	/// </summary>
	void displayBuffer();

private:
	int m_row;
	int m_col;
	HANDLE m_bufferHandle;
	WORD m_defaultAttribute;
	Window* m_window;
	CHAR_INFO** m_buffer;
};

