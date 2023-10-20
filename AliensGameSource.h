#pragma once
#include "GameSource.h"
#include "Alien.h"
#include "Barrier.h"
#include "Player.h"

#define ALIENT_COUNT 20
#define BARRIER_COUNT 5

class AliensGameSource :
    public GameSource
{
public:

	AliensGameSource() : m_ground ( 160 )
	{

	}

	void initaliseGame() override;
	//void processInput() override;
	//void updateGame() override;
	void drawGame() override;

	void setAlientPositions();
	void setBarrierPositions();

protected:
	bool drawChar(ostream& o, int& row, int& column);

private:

	/* Game specific member variables*/
	Player m_player;
	Alien m_aliens[ALIENT_COUNT];
	Barrier m_barriers[BARRIER_COUNT];
	Ground m_ground;

	void playMuisc(KEY_EVENT_RECORD ker);
};

