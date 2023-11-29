#include "KeyboardInput.h"

KeyboardInput::KeyboardInput()
{
}

KeyboardInput::KeyboardInput ( HANDLE bufferHandle ) : m_bufferHandle ( bufferHandle )
{
    if ( m_bufferHandle == INVALID_HANDLE_VALUE )
    {
        return;
    }

    init ( );
}

KeyboardInput::~KeyboardInput ( )
{
    m_keyRegistrations.clear ( );

    if (m_ready)
    {
        // reset console mode
        SetConsoleMode(m_bufferHandle, fdwSaveOldMode);
    }

    for ( auto & key : m_keyRegistrations )
    {
        delete key.second;
    }
}

void KeyboardInput::tick ( const float deltaTime )
{
    if ( !m_ready )
    {
        return;
    }

    for ( auto & key : m_keyRegistrations )
    {
        auto result = GetAsyncKeyState ( key.first );

        if ( result & 0x8000 ) // check most significant bit
        {
            // key is down
            if ( key.second->isPressed )
            {
                key.second->pressedDuration += deltaTime;
            }
            else
            {
                key.second->isPressed = true;
                key.second->pressedDuration = 0;
                if ( key.second->onPressCallback != nullptr )
                {
                    key.second->onPressCallback ( key.first, result );
                }
            }
        }
        else
        {
            // key is up
            if ( key.second->isPressed )
            {
                key.second->isPressed = false;
            }
        }

    }
}

bool KeyboardInput::registerKey ( WORD key )
{
    if ( !m_ready )
    {
        return false;
    }

    if ( m_keyRegistrations.find ( key ) != m_keyRegistrations.end ( ) )
    {
        // this key has already been registered.
        return true;
    }

    auto data = new keyEventStatus ( );
    data->onPressCallback = nullptr;

    m_keyRegistrations [ key ] = data;
    return true;
}

bool KeyboardInput::registerOnKey ( WORD key, std::function<void ( WORD , short  )> callback )
{
    if ( !m_ready )
    {
        return false;
    }

    if ( m_keyRegistrations.find ( key ) != m_keyRegistrations.end ( ) )
    {
        // this key has already been registered.
        delete m_keyRegistrations [ key ];
    }

    auto data = new keyEventStatus ( );
    data->onPressCallback = callback;

    m_keyRegistrations [ key ] = data;
    return true;
}

bool KeyboardInput::wasPressThisFrame ( WORD key )
{
    auto const status = m_keyRegistrations [ key ];
    return status->isPressed && status->pressedDuration == 0;
}

bool KeyboardInput::isPressed ( WORD key )
{
    return m_keyRegistrations [ key ]->isPressed;
}

void KeyboardInput::init ( )
{
    // FC note to self this function probably should be moved outside of the keyboard input
    // and into somewhere that handles the console setup specifically.

    // Save the current input mode, to be restored on exit.
    if ( !GetConsoleMode ( m_bufferHandle, &fdwSaveOldMode ) )
    {
        return;
    }

    // Enable the window and mouse input events.
    // ENABLE_EXTENDED_FLAGS without ENABLE_QUICK_EDIT_MODE will disable quick edit mode.
    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
    if ( !SetConsoleMode ( m_bufferHandle, fdwMode ) )
    {
        return;
    }

    m_ready = true;
}
