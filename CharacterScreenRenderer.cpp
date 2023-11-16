#include "CharacterScreenRenderer.h"

#define ESC "\x1b"
#define CSI "\x1b["
#define ENABLE_ALTERNATE_MODE "?1049h"
#define DISABLE_ALTERNATE_MODE "?1049l"
#define CLEAR_SCREEN "2J"


CharacterScreenRenderer::CharacterScreenRenderer(HANDLE bufferHandle)
{
}

CharacterScreenRenderer::CharacterScreenRenderer(HANDLE bufferHandle, int width, int height)
{
	hConsoleHandle = bufferHandle;
	m_width = width;
	m_height = height;
	setBackgroundColour(0, 0, 0); // Black
	initBuffer();
}

CharacterScreenRenderer::~CharacterScreenRenderer()
{
	if (ready)
	{
		ready = false;
		enterCommand(DISABLE_ALTERNATE_MODE);
		SetConsoleMode(hConsoleHandle, fdwSaveOldMode);
	}
}

void CharacterScreenRenderer::setCursorVisibility(bool visible)
{
	char cmd[4] = { '?', '2', '5', '?' };
	cmd[3] = visible ? 'h' : 'l';
	enterCommand(cmd);
}

void CharacterScreenRenderer::setBackgroundColour(byte r, byte g, byte b)
{
	m_backgroundColour.rgbtRed = r;
	m_backgroundColour.rgbtGreen = g;
	m_backgroundColour.rgbtBlue = b;
}

void CharacterScreenRenderer::enterCommand(const char* cmd)
{
	printf(CSI "%s", cmd);
}

void CharacterScreenRenderer::enterSequence(const char* cmd)
{
	printf(ESC "%s", cmd);
}

int CharacterScreenRenderer::getWidth()
{
	return m_width;
}

int CharacterScreenRenderer::getHeight()
{
	return m_height;
}

void CharacterScreenRenderer::draw()
{
	
	enterCommand(CLEAR_SCREEN);

	// draw background
	char cmd[25];
	sprintf_s(cmd, "48;2;%i;%i;%im", m_backgroundColour.rgbtRed, m_backgroundColour.rgbtGreen, m_backgroundColour.rgbtBlue);
	enterCommand(cmd);

	//printf(ESC "(0"); // Enter Line drawing mode
	//printf("x"); // in line drawing mode, \x78 -> \u2502 "Vertical Bar"

	//printf(CSI "0m"); // restore color
	//printf(ESC "(B"); // exit line drawing mode

	//moveCursor(1, 1);
	//printf("%i", frame);
	//frame++;
}


bool CharacterScreenRenderer::initBuffer()
{
	if (!GetConsoleMode(hConsoleHandle, &fdwSaveOldMode))
	{
		// error has occurred
		return false;
	}

	DWORD setting = fdwSaveOldMode;
	setting |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if (!SetConsoleMode(hConsoleHandle, setting))
	{
		// error setting virtual mode
		return false;
	}

	enterCommand(ENABLE_ALTERNATE_MODE);
	enterCommand(CLEAR_SCREEN);
	setCursorVisibility(false);
	ready = true;
	return true;
}

void CharacterScreenRenderer::moveCursor(int c, int l)
{
	printf(CSI "%i;%iH", l, c);
}

void CharacterScreenRenderer::moveCursorToLastLine()
{
	moveCursor(1, m_height);
}

void CharacterScreenRenderer::moveCursorToFirstLine()
{
	moveCursor(1, 1);
}
