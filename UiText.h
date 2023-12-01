#pragma once
#include "GameObject.h"
#include <string>
#include <stdio.h>
#include <stdarg.h>

class UiText :
    public GameObject
{
public:
	UiText ( const char * format, const int maxLength ) :
		GameObject ( 0, 1 ), m_format ( nullptr ), m_length ( maxLength ), m_string ( nullptr )
	{
		m_string = new char [ maxLength ];
		memset ( m_string, '\0', maxLength );
		
		auto formatLength = strlen ( format ) + 1;
		m_format = new char [ formatLength ];
		
		strcpy_s ( m_format, formatLength, format );
	}

	~UiText ( )
	{
		delete [ ] m_string;
		delete [ ] m_format;
	}

	template<typename... Args> void updateText ( Args... args )
	{
		if ( m_format == nullptr )
		{
			return;
		}

		m_width = sprintf_s ( m_string, m_length, m_format, args... );
	}

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return m_string;
	};

private:

	char * m_string;
	size_t m_length;
	char * m_format;

};

