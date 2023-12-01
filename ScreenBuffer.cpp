#include "ScreenBuffer.h"

#define DEFAULT_ATTRIBUTE Colour::Fore_White | Colour::Back_Black

#pragma region Constructors, destructors, and operators

/// <summary>
/// Sets all characters in the buffer to the space character i.e. ' '.
/// </summary>
ScreenBuffer::ScreenBuffer ( const int x, const int y )
	: m_col ( x ),
	m_row ( y ),
	m_buffer ( nullptr ),
	m_rowPtr ( nullptr ),
	m_bufferHandle ( nullptr ),
	m_defaultAttribute ( DEFAULT_ATTRIBUTE )
{
	// allocate a single continuous block of memory big enough to story the whole screen buffer.
	m_buffer = new CHAR_INFO [ m_row * m_col ];

	// establish pointers to each row in the continuous block of memory.
	// this allows for get/sets to operate as if they have a 2D array.
	m_rowPtr = new CHAR_INFO * [ m_row ];
	for ( int i = 0; i < m_row; i++ )
	{
		m_rowPtr [ i ] = &m_buffer [ i * m_col ];
	}

	m_bufferHandle = CreateConsoleScreenBuffer (
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL );

	if ( m_bufferHandle == INVALID_HANDLE_VALUE )
	{
		throw;
	}

	if ( !SetConsoleActiveScreenBuffer ( m_bufferHandle ) )
	{
		cout << "SetConsoleActiveScreenBuffer failed with error " << GetLastError ( ) << endl;
		throw;
	}

	m_window = new Window ( m_bufferHandle );
	m_window->setWindow ( m_col, m_row );

	clearBuffer ( );
}

// Copy constructor
ScreenBuffer::ScreenBuffer ( const ScreenBuffer & other )
	: m_col ( other.m_row ),
	m_row ( other.m_col ),
	m_buffer ( nullptr ),
	m_rowPtr ( nullptr ),
	m_bufferHandle ( other.m_bufferHandle ),
	m_defaultAttribute ( other.m_defaultAttribute )
{
	m_window = new Window ( *other.m_window );

	// allocate a single continuous block of memory big enough to story the whole screen buffer.
	m_buffer = new CHAR_INFO [ m_row * m_col ];

	// establish pointers to each row in the continuous block of memory.
	// this allows for get/sets to operate as if they have a 2D array.
	m_rowPtr = new CHAR_INFO * [ m_row ];
	for ( int i = 0; i < m_row; i++ )
	{
		m_rowPtr [ i ] = &m_buffer [ i * m_col ];
	}

	// Copy the data from other to this object
	memcpy ( m_buffer, other.m_buffer, m_row * m_col * sizeof ( CHAR_INFO ) );
}

// move constructor
ScreenBuffer::ScreenBuffer ( ScreenBuffer && other ) noexcept
	: m_col ( 0 ),
	m_row ( 0 ),
	m_buffer ( nullptr ),
	m_rowPtr ( nullptr ),
	m_bufferHandle ( nullptr ),
	m_defaultAttribute ( DEFAULT_ATTRIBUTE )
{
	// https://learn.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170#robust-programming
	*this = std::move ( other );
}

// destructor
ScreenBuffer::~ScreenBuffer ( )
{
	delete [ ] m_buffer;
	delete [ ] m_rowPtr;
}

// Copy operator 
ScreenBuffer & ScreenBuffer::operator=( const ScreenBuffer & other ) // Copy Assignment Operator
{
	if ( this == &other )
	{
		return *this;
	}

	// Deallocate existing memory
	delete [ ] m_buffer;
	delete [ ] m_rowPtr;

	// Allocate memory for new data
	m_row = other.m_row;
	m_col = other.m_col;
	m_bufferHandle = other.m_bufferHandle;
	m_defaultAttribute = other.m_defaultAttribute;
	m_window = new Window ( *other.m_window );

	// allocate a single continuous block of memory big enough to story the whole screen buffer.
	m_buffer = new CHAR_INFO [ m_row * m_col ];

	// establish pointers to each row in the continuous block of memory.
	// this allows for get/sets to operate as if they have a 2D array.
	m_rowPtr = new CHAR_INFO * [ m_row ];
	for ( int i = 0; i < m_row; i++ )
	{
		m_rowPtr [ i ] = &m_buffer [ i * m_col ];
	}

	memcpy ( m_buffer, other.m_buffer, m_row * m_col * sizeof( CHAR_INFO ) );

	return *this;
}

// Move operator
ScreenBuffer & ScreenBuffer::operator=( ScreenBuffer && other ) noexcept
{
	if ( this == &other )
	{
		return *this;
	}

	// Deallocate existing memory
	delete [ ] m_buffer;
	delete [ ] m_rowPtr;

	// Copy data from source object.
	m_row = other.m_row;
	m_col = other.m_col;
	m_bufferHandle = other.m_bufferHandle;
	m_defaultAttribute = other.m_defaultAttribute;
	m_window = other.m_window;
	m_rowPtr = other.m_rowPtr;

	// Release the data pointer from the source object so that
	// the destructor does not free the memory multiple times.
	m_row = 0;
	m_col = 0;
	m_defaultAttribute = DEFAULT_ATTRIBUTE;
	m_window = nullptr;
	m_bufferHandle = nullptr;
	m_buffer = nullptr;
	m_rowPtr = nullptr;

	return *this;
}

#pragma endregion

#pragma region Getters / Setters

char ScreenBuffer::getChar ( const int x, const int y ) const
{
	// is this doing a copy?
	return m_rowPtr [ y ][ x ].Char.UnicodeChar;
}

void ScreenBuffer::setChar ( const int x, const int y, char c )
{
	m_rowPtr [ y ][ x ].Char.UnicodeChar = c;
}

#pragma endregion

#pragma region Colours

void ScreenBuffer::setCharColour ( const int x, const int y, Colour foreground, Colour background )
{
	m_rowPtr [ y ][ x ].Attributes &= ~0x0077;
	m_rowPtr [ y ][ x ].Attributes |= ( foreground | background );
}

void ScreenBuffer::setBackgroundColour ( Colour background )
{
	m_defaultAttribute &= ~Back_White;
	m_defaultAttribute |= background;
}

void ScreenBuffer::setForegroundColour ( Colour foreground )
{
	m_defaultAttribute &= ~Fore_White;
	m_defaultAttribute |= foreground;
}

#pragma endregion

void ScreenBuffer::clearBuffer ( )
{
	CHAR_INFO defaultInfo;

	defaultInfo.Char.UnicodeChar = ' ';
	defaultInfo.Attributes = m_defaultAttribute;

	int length = m_row * m_col;

	for ( int i = 0; i < length ; i++ )
	{
		m_buffer [ i ] = defaultInfo;
	}
}

/// <summary>
/// Copies the contents of the local buffer to the output buffer.
/// Then makes the output buffer active.
/// The local buffer is then cleared.
/// </summary>
void ScreenBuffer::displayBuffer ( )
{
	if ( m_bufferHandle == nullptr )
	{
		throw;
		return;
	}

	COORD dwBufferSize;
	dwBufferSize.X = m_col;
	dwBufferSize.Y = m_row;

	COORD dwBufferCoord;
	dwBufferCoord.X = 0;
	dwBufferCoord.Y = 0;

	SMALL_RECT writeRegion;
	writeRegion.Top = 0;
	writeRegion.Left = 0;
	writeRegion.Bottom = m_row - 1;
	writeRegion.Right = m_col - 1;

	auto result = WriteConsoleOutput (
		m_bufferHandle,
		m_rowPtr [ 0 ],
		dwBufferSize,
		dwBufferCoord,
		&writeRegion
	);

	if ( !result )
	{
		printf ( "WriteConsoleOutput  failed - (%d)\n", GetLastError ( ) );
		throw;
	}

	SetConsoleActiveScreenBuffer ( m_bufferHandle );

	clearBuffer ( );
}
