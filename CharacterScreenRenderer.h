#pragma once
#include <windows.h>

// Standard library C-style
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <format>

class CharacterScreenRenderer
{

private:
	
	bool initBuffer();
	
	HANDLE hConsoleHandle;
	DWORD fdwSaveOldMode;
	bool ready;
	int frame;
	int m_width;
	int m_height;

public:

	CharacterScreenRenderer(HANDLE bufferHandle);
	CharacterScreenRenderer(HANDLE bufferHandle, int width, int height);
	~CharacterScreenRenderer();

	void draw();
	void setCursorVisibility(bool visible);
	void setBackgroundColour(byte r, byte g, byte b);
	void moveCursor(int r, int c);
	void moveCursorToLastLine();
	void moveCursorToFirstLine();
	void enterCommand(const char* cmd);
	void enterSequence(const char* cmd);

	int getWidth();
	int getHeight();
	
	RGBTRIPLE m_backgroundColour;
};

