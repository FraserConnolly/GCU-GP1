/*
* Created By: Fraser Connolly
* Created Date: 2023-10-12
*/

#pragma once
#include <iostream>
#include "GameObject.h"

class Ground
	: public GameObject
{

public:

	Ground ( int width ) : GameObject ( width, 1 )
	{
		for ( int i = 0; i < sizeof ( ground ); i++ )
		{
			ground [ i ] = ( i <= width ? '_' : '\0' );
		}
	}

	// Inherited via GameObject
	const char * draw ( ) const override
	{
		return ground;
	};

private:

	char ground [ 600 ];

};
