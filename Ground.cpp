/*
* Created By: Fraser Connolly
* Created Date: 2023-10-05
*/

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Ground
{
public:
	
	void draw(int width, int height)
	{
		for (int i = 0; i <= height; i++)
		{
			if (i == height)
			{
				for (int j = 0; j < width; j++)
				{
					cout << "_";
				}
			}
			else
			{
				cout << endl;
			}
		}
	}


private:

};

