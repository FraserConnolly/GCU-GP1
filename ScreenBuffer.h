#pragma once
#include "Window.h"
#include "RenderCellData.h"

// note that in Lab 8 Bryan Young has this declared as a struct.
class ScreenBuffer
{
public:

	ScreenBuffer(const int x, const int y);

	ScreenBuffer(const ScreenBuffer& other );		// Copy constructor
	ScreenBuffer(ScreenBuffer&& other) noexcept;	// Move constructor

	ScreenBuffer& operator=(const ScreenBuffer& other);		// Copy Assignment Operator
	ScreenBuffer& operator=(ScreenBuffer&& other) noexcept;	// Move Assignment Operator

	~ScreenBuffer();

	char getChar(const int x, const int y) const;
	void setChar(const int x, const int y, char c);
	void setCharColour(const int x, const int y, CellColour cellColour);
	void setCharColour(const int x, const int y, CellColour foreground, CellColour background);
	void setBackgroundColour(const CellColour background);
	void setForegroundColour(const CellColour foreground);
	void applyRenderData ( const int x, const int y, const unsigned int width, const unsigned int height, const pRenderCellData data );

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
	CHAR_INFO * m_buffer;
	CHAR_INFO ** m_rowPtr;
};

