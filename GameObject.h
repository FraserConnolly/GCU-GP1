#pragma once
class GameObject
{
public:

	GameObject ( const int width, const int height )
		: m_width ( width ), m_height ( height ),
		m_X ( 0 ), m_Y ( 0 )
	{ }

	// =0 marks this function as a pure virtual void (i.e. abstract)
	virtual const char * draw ( ) const = 0;

	bool inPosition ( const int x, const int y ) const
	{
		return ( x == m_X && y == m_Y );
	}

	const int getHeight ( ) const
	{
		return m_height;
	}
	
	const int getWidth ( ) const
	{
		return m_width;
	}

	int m_X;
	int m_Y;

protected:
	int m_height;
	int m_width;
};

