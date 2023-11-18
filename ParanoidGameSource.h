#pragma once
#include "GameSource.h"

class ParanoidGameSource :
	public GameSource
{
public:

	ParanoidGameSource() 
	{ }

	void initaliseGame() override;
	//void processInput( ) override;
	//void updateGame( ) override;
	void drawGame() override;


protected:
	bool drawChar(ostream& o, int& row, int& column);

private:

	/* Game specific member variables*/

	void playMuisc(KEY_EVENT_RECORD ker);

};

