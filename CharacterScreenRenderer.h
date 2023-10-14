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
	void moveCursor(int r, int c);
	void enterCommand(const char * cmd);
	
	HANDLE hConsoleHandle;
	DWORD fdwSaveOldMode;
	BOOL ready;
	int frame;

public:

	CharacterScreenRenderer(HANDLE bufferHandle);
	~CharacterScreenRenderer();

	void draw();
	void setCursorVisibility(bool visible);
	void setBackgroundColour(byte r, byte g, byte b);
	RGBTRIPLE m_backgroundColour;
};

