#pragma once
#include "GameSource.h"

class ParanoidGameSource :
	public GameSource
{
public:

	ParanoidGameSource() 
	{ }

	void initaliseGame() override;
	void updateGame( ) override;
	void drawGame() override;


protected:
	void initaliseLevel( ) override;

private:

	/* Game specific member variables*/

	void playMuisc( );

};

