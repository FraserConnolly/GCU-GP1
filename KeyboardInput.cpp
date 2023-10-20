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
    keyRegistrations.clear ( );
}

void KeyboardInput::tick ( )
{
    if ( !m_ready )
    {
        return;
    }

    INPUT_RECORD irInBuf [ 128 ];
    DWORD cNumRead;             // records read
    DWORD eventsInBuffer = 0;
    if ( !GetNumberOfConsoleInputEvents ( m_bufferHandle, &eventsInBuffer ) || eventsInBuffer == 0 )
    {
        // no events to process
        return;
    }

    if ( !ReadConsoleInput (
        m_bufferHandle,     // input buffer handle
        irInBuf,            // buffer to read into
        128,                // size of read buffer
        &cNumRead ) )         // number of records read
    {
        //ErrorExit("ReadConsoleInput");
        return;
    }

    for ( DWORD i = 0; i < cNumRead; i++ )
    {
        switch ( irInBuf [ i ].EventType )
        {
            case KEY_EVENT: // keyboard input
                KeyEventProc ( irInBuf [ i ].Event.KeyEvent );
                break;

            case WINDOW_BUFFER_SIZE_EVENT: // screen buffer resizing
                //ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
                break;

            case MOUSE_EVENT:  // disregard mouse input
            case FOCUS_EVENT:  // disregard focus events
            case MENU_EVENT:   // disregard menu events
                break;

            default:
                //ErrorExit("Unknown event type");
                break;
        }
    }
}

VOID KeyboardInput::KeyEventProc ( KEY_EVENT_RECORD ker )
{
    if ( keyRegistrations.find ( ker.wVirtualKeyCode ) == keyRegistrations.end ( ) )
    {
        // no registrations
        return;
    }

    keyRegistrations [ ker.wVirtualKeyCode ] ( ker );
}

bool KeyboardInput::registerOnKey ( WORD key, std::function<void ( KEY_EVENT_RECORD )> callback )
{
    if ( !m_ready )
    {
        return false;
    }

    keyRegistrations [ key ] = callback;
    return true;
}

void KeyboardInput::init ( )
{
    // Save the current input mode, to be restored on exit.

    if ( !GetConsoleMode ( m_bufferHandle, &fdwSaveOldMode ) )
    {
        //ErrorExit("GetConsoleMode");
        return;
    }

    // Enable the window and mouse input events.

    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if ( !SetConsoleMode ( m_bufferHandle, fdwMode ) )
    {
        //ErrorExit("SetConsoleMode");
        return;
    }

    m_ready = true;
}
