/*
* Created By: Fraser Connolly
* Created Date: 2023-10-12
*/

#pragma once
#include <iostream>

class Ground
{

public:

	void draw(int width, int height);

private:

	void drawChar(std::ostream& o, char c);
	void drawChar(std::ostream& o, char c, int count);

};
