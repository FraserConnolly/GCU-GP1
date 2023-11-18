#include "ScreenBuffer.h"

/// <summary>
/// Sets all characters in the buffer to the space character i.e. ' '.
/// </summary>
ScreenBuffer::ScreenBuffer(const int x, const int y)
	: col(x), row(y), m_buffer(nullptr), m_bufferHandle(nullptr), m_defaultAttribute(Colour::Fore_White | Colour::Back_Black)
{
	m_buffer = new CHAR_INFO * [row];
	for (int i = 0; i < row; i++)
	{
		m_buffer[i] = new CHAR_INFO[col];
	}

	m_bufferHandle = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);

	if (m_bufferHandle == INVALID_HANDLE_VALUE)
	{
		throw;
	}
	
	if (!SetConsoleActiveScreenBuffer(m_bufferHandle))
	{
		cout << "SetConsoleActiveScreenBuffer failed with error " << GetLastError() << endl;
		throw;
	}

	m_window = new Window(m_bufferHandle);
	m_window -> setWindow(col, row);

	clearBuffer();
}

ScreenBuffer::~ScreenBuffer()
{
	for (int i = 0; i < row; i++)
	{
		delete m_buffer[i];
	}
	delete m_buffer;
}

char ScreenBuffer::getChar(const int x, const int y) const
{
	// is this doing a copy?
	return m_buffer[y][x].Char.UnicodeChar;
}

void ScreenBuffer::setChar(const int x, const int y, char c)
{
	m_buffer[y][x].Char.UnicodeChar = c;
}

void ScreenBuffer::setCharColour(const int x, const int y, Colour foreground, Colour background)
{
	m_buffer[y][x].Attributes &= ~0x0077;
	m_buffer[y][x].Attributes |= ( foreground | background );
}

void ScreenBuffer::setBackgroundColour(Colour background)
{
	m_defaultAttribute &= ~Back_White;
	m_defaultAttribute |= background;
}

void ScreenBuffer::setForegroundColour(Colour foreground)
{
	m_defaultAttribute &= ~Fore_White;
	m_defaultAttribute |= foreground;
}

void ScreenBuffer::clearBuffer()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			CHAR_INFO* c = &m_buffer[i][j];

			c->Char.UnicodeChar = ' ';
			c->Attributes = m_defaultAttribute;
		}
	}
}

/// <summary>
/// Copies the contents of the local buffer to the output buffer.
/// Then makes the output buffer active.
/// The local buffer is then cleared.
/// </summary>
void ScreenBuffer::displayBuffer()
{
	COORD dwBufferSize;
	dwBufferSize.X = col;
	dwBufferSize.Y = 1;

	COORD dwBufferCoord;
	dwBufferCoord.X = 0;
	dwBufferCoord.Y = 0;

	SMALL_RECT writeRegion;
	writeRegion.Top = 0;
	writeRegion.Left = 0;
	writeRegion.Bottom = row - 1;
	writeRegion.Right = col - 1;

	SetConsoleActiveScreenBuffer(m_bufferHandle);

	for (int i = 0; i < row; i++)
	{
		writeRegion.Top = i;
		writeRegion.Bottom = i;
		writeRegion.Right = col - 1;

		auto result = WriteConsoleOutput(
			m_bufferHandle,
			m_buffer[i],
			dwBufferSize,
			dwBufferCoord,
			&writeRegion
		);

		if (!result)
		{
			printf("WriteConsoleOutput  failed - (%d)\n", GetLastError());
			throw;
		}

	}

	SetConsoleActiveScreenBuffer(m_bufferHandle);

	clearBuffer();
}
