#pragma once
#include <windows.h>

// Standard library C-style
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>

class KeyboardInput
{

public:

	KeyboardInput(HANDLE bufferHandle);
	~KeyboardInput();

	void tick();

	bool registerOnKey( WORD key, void(* callback)(KEY_EVENT_RECORD) );

private:
	HANDLE m_bufferHandle;
	BOOL m_ready;
	DWORD fdwSaveOldMode;
	
	void init();
	VOID KeyEventProc(KEY_EVENT_RECORD ker);
	std::map<WORD, void(*)(KEY_EVENT_RECORD)> keyRegistrations;

};

