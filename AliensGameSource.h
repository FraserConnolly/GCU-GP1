#pragma once
#include "GameSource.h"
#include "Alien.h"
#include "Barrier.h"
#include "Player.h"

#define ALIENT_COUNT 20
#define BARRIER_COUNT 20

class AliensGameSource :
    public GameSource
{
public:

	//void processInput() override;
	//void updateGame() override;
	void drawGame() override;

	void setAlientPositions();
	void setBarrierPositions();

private:
	/* Game specific member variables*/
	Player m_player;
	Alien m_aliens[ALIENT_COUNT];
	Barrier m_barriers[BARRIER_COUNT];
	Ground m_ground;
};

