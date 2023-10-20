#pragma once
class GameObject
{
public:

	GameObject ( int width, int height )
		: m_width ( width ), m_height ( height ),
		m_X ( 0 ), m_Y ( 0 )
	{ }

	// =0 marks this function as a pure virtual void (i.e. abstract)
	virtual char * draw ( ) = 0;

	bool inPosition ( int x, int y )
	{
		return ( x == m_X && y == m_Y );
	}

	int getHeight ( )
	{
		return m_height;
	}
	int getWidth ( )
	{
		return m_width;
	}

	int m_X;
	int m_Y;

protected:
	int m_height;
	int m_width;
};

