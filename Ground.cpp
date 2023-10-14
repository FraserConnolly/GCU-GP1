/*
* Created By: Fraser Connolly
* Created Date: 2023-10-05
* 
* 2023-10-12 Separated decelerations from definitions.
* 2023-10-14 Stopped using the string class as it has several calls to allocate and deallocate for every usage.
*/

#include "Ground.h"

using namespace std;
	
void Ground :: draw(int width, int height)
{
	for (int i = 0; i <= height; i++)
	{
		i == height ? drawChar(cout, '_', width) : drawChar(cout, '\n' ); 
	}
}

inline void Ground :: drawChar(ostream& o, char c)
{
	o << c;
}

inline void Ground :: drawChar(ostream &o, char c, int count )
{
	for (int i = 0; i <= count; i++)
	{
		o << c;
	}
}

