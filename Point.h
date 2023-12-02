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

} Point, *pPoint;