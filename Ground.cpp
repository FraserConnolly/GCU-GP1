/*
* Created By: Fraser Connolly
* Created Date: 2023-10-05
*/

#pragma once
#include <iostream>
#include <string>
#include "CharacterScreenRenderer.h"

using namespace std;

class Ground
{
public:
	
	Ground(CharacterScreenRenderer * renderer)
	{
		m_renderer = renderer;
	}

	void draw()
	{
		m_renderer->moveCursorToLastLine();
		m_renderer->enterSequence("(0"); // enable line drawing mode
		printf("q");
		/*for (int i = 0; i < 1; i++)
		{
		}*/
		m_renderer->enterSequence("(B"); // enable ASCII mode
	}


private:

	CharacterScreenRenderer* m_renderer;
};

