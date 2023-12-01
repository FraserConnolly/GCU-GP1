#pragma once

/// <summary>
/// This is the underlying class for all game objects that exist on the console grid.
/// 
/// Coordinates:
/// Each game object exits on a grid however it uses a float data type to store its location.
/// This is to allow an object to move by less than a grid unit each frame.
/// </summary>
class GameObject
{
public:

	const int CELL_WIDTH  = 8;
	const int CELL_HEIGHT = 16;

	GameObject ( const int width, const int height )
		: m_width ( width ), m_height ( height ),
		m_X ( 0 ), m_Y ( 0 ), m_gridX( 0 ), m_gridY( 0 ),
		m_active( true )
	{ }

	// =0 marks this function as a pure virtual void (i.e. abstract)
	virtual const char * draw ( ) const = 0;

	bool inPosition ( const int x, const int y ) const
	{
		return ( x == getGridX ( ) && y == getGridY ( ) );
	}

	bool hasCollided ( const GameObject & coll )
	{

		if (         m_width == 0 ||      m_height == 0
			 || coll.m_width == 0 || coll.m_height == 0 )
		{
			// either self or the other object has an area of 0 so there can be no collision.
			return false;
		}

		// note that height and width must have -1 as anything with a dimension less than 1 will not occupy a grid space.

		if ( m_gridX > coll.m_gridX + coll.m_width - 1 || coll.m_gridX > m_gridX + m_width - 1 )
		{
			// one rectangle is on left side of the other
			return false;
		}

		if ( m_gridY + m_height - 1 > coll.m_gridY || coll.m_gridY + coll.m_height - 1 > m_gridY )
		{
			// one rectangle is above the other
			return false;
		}

		return true;
	}

	const int getHeight ( ) const
	{
		return m_height;
	}
	
	const int getWidth ( ) const
	{
		return m_width;
	}

	const float getX ( ) const
	{
		return m_X;
	}

	const int getGridX ( ) const
	{
		return m_gridX;
	}

	const float getY ( ) const
	{
		return m_Y;
	}

	const int getGridY ( ) const
	{
		return m_gridY;
	}

	void setX ( float x )
	{
		m_X = x;
		m_gridX = int ( x / CELL_WIDTH );
	}

	void setGridX ( int x )
	{
		m_X = float ( x * CELL_WIDTH );
		m_gridX = x;
	}

	void setY ( float y )
	{
		m_Y = y;
		m_gridY = int ( y / CELL_HEIGHT );
	}

	inline void setGridY ( int y )
	{
		m_Y = float ( y * CELL_HEIGHT );
		m_gridY = y;
	}

	inline void setGridPosition ( int x, int y )
	{
		setGridX ( x );
		setGridY ( y );
	}

	void translate ( float x, float y )
	{
		setX ( m_X + x );
		setY ( m_Y + y );
	}

	void translateByGridUnit ( int x, int y )
	{
		setX ( m_X + ( x * CELL_WIDTH ) );
		setY ( m_Y + ( y * CELL_HEIGHT ) );
	}

	void setActive ( bool active )
	{
		m_active = active;
	}

	const bool getActive ( ) const
	{
		return m_active;
	}

protected:

	int m_height;
	int m_width;
	bool m_active;

private:

	float m_X;
	int m_gridX;
	float m_Y;
	int m_gridY;

};

