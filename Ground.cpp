/*
* Created By: Fraser Connolly
* Created Date: 2023-10-05
* 
* 2023-10-12 Seperated declerations from definitions.
*/

#include "Ground.h"

using namespace std;
	
void Ground :: draw(int width, int height)
{
	for (int i = 0; i <= height; i++)
	{
		// the string constructor used here repeats the underscore character the number of times specified in the first parameter.
		i == height ? cout << std::string(width, '_') : cout << std::endl ;
	}
}


