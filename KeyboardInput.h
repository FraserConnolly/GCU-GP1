#pragma once
#include <windows.h>

// Standard library C-style
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <functional>

class KeyboardInput
{

public:

	KeyboardInput();
	KeyboardInput(HANDLE bufferHandle);
	~KeyboardInput();

	void tick();

	bool registerOnKey(WORD key, std::function<void(KEY_EVENT_RECORD)> callback);
private:
	HANDLE m_bufferHandle = NULL;
	BOOL m_ready = false;
	DWORD fdwSaveOldMode = 0;
	
	void init();
	VOID KeyEventProc(KEY_EVENT_RECORD ker);
	std::map<WORD, std::function<void(KEY_EVENT_RECORD)>> keyRegistrations;

};

