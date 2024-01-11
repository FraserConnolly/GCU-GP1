#pragma once
#include <windows.h>

// Standard library C-style
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <functional>

typedef struct
{
	bool isPressed;
	float pressedDuration;
	std::function<void ( WORD key, short status )> onPressCallback;
} keyEventStatus, *pKeyEventStatus;


class KeyboardInput
{

public:

	KeyboardInput ( );
	KeyboardInput ( HANDLE bufferHandle );
	~KeyboardInput ( );

	void tick ( const float deltaTime );

	bool registerKey ( WORD key );
	bool registerOnKey ( WORD key, std::function<void ( WORD, short )> callback );

	bool wasPressedThisFrame ( WORD key );
	bool isPressed ( WORD key );

	// Call this whenever the scene loads to ensure that key holds are reset
	void resetKeyPresses ( );

private:
	HANDLE m_bufferHandle = nullptr;
	BOOL m_ready = false;
	DWORD fdwSaveOldMode = 0;
	
	void init ( );
	std::map<WORD, pKeyEventStatus> m_keyRegistrations;

};
