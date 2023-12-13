#pragma once

typedef struct _point
{
	_point ( )
		: X ( 0 ), Y ( 0 )
	{
	}

	_point ( const int x, const int y )
		: X ( x ), Y ( y )
	{
	}

	int X;
	int Y;
	
	inline bool operator == (const _point & other) const
	{
		return X == other.X && Y == other.Y;
	}

	inline bool operator != (const _point& other) const 
	{
		return !(operator==(other));
	}

	inline _point& operator *=(const int v)
	{
		X *= v;
		Y *= v;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _point operator*(const int v) const
	{
		_point p;

		p.X = X * v;
		p.Y = Y * v;

		return p;
	}

	inline _point& operator +=(const _point& v)
	{
		X += v.X;
		Y += v.Y;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _point operator+(const _point& v) const
	{
		_point p;

		p.X = X + v.X;
		p.Y = Y + v.Y;

		return p;
	}

	inline _point& operator -=(const _point& v)
	{
		X -= v.X;
		Y -= v.Y;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _point operator-(const _point& v) const
	{
		_point p;

		p.X = X - v.X;
		p.Y = Y - v.Y;

		return p;
	}

	inline _point& operator +=(const int v)
	{
		X += v;
		Y += v;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _point operator+(const int v) const
	{
		_point p;

		p.X = X + v;
		p.Y = Y + v;

		return p;
	}

	inline _point& operator -=(const int v)
	{
		X -= v;
		Y -= v;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _point operator-(const int v) const
	{
		_point p;

		p.X = X - v;
		p.Y = Y - v;

		return p;
	}

} Point, *pPoint;

typedef struct _fPoint
{
	_fPoint()
		: X(0), Y(0)
	{
	}

	_fPoint(const float x, const float y)
		: X(x), Y(y)
	{
	}
	
	inline bool operator == (const _fPoint& other) const
	{
		return X == other.X && Y == other.Y;
	}

	inline bool operator != (const _fPoint& other) const
	{
		return !(operator==(other));
	}

	inline _fPoint& operator +=(const _fPoint& v)
	{
		X += v.X;
		Y += v.Y;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _fPoint operator+(const _fPoint& v) const
	{
		_fPoint p;

		p.X = X + v.X;
		p.Y = Y + v.Y;

		return p;
	}

	inline _fPoint& operator -=(const _fPoint& v)
	{
		X -= v.X;
		Y -= v.Y;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _fPoint operator-(const _fPoint& v) const
	{
		_fPoint p;

		p.X = X - v.X;
		p.Y = Y - v.Y;

		return p;
	}

	inline _fPoint& operator *=(const float v)
	{
		X *= v;
		Y *= v;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _fPoint operator*(const float v) const
	{
		_fPoint p;
		
		p.X = X * v;
		p.Y = Y * v;

		return p;
	}

	inline _fPoint& operator +=(const float v)
	{
		X += v;
		Y += v;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _fPoint operator+(const float v) const
	{
		_fPoint p;

		p.X = X + v;
		p.Y = Y + v;

		return p;
	}

	inline _fPoint& operator -=(const float v)
	{
		X -= v;
		Y -= v;

		// Assignment operator returns left side of assignment.
		return *this;
	}

	inline _fPoint operator-(const float v) const
	{
		_fPoint p;

		p.X = X - v;
		p.Y = Y - v;

		return p;
	}

	float X;
	float Y;

} FPoint, * pFPoint;