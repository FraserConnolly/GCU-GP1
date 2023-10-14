/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
*/

#include "GameSource.h"

GameSource game;

void quit(KEY_EVENT_RECORD);
void spacebarPressed(KEY_EVENT_RECORD ker);

int main()
{
	game.initaliseGame();

	game.kInput.registerOnKey(VK_SPACE, spacebarPressed);
	game.kInput.registerOnKey(VK_ESCAPE, quit);

	game.gameLoop();

	return 0;
}

void spacebarPressed(KEY_EVENT_RECORD ker)
{
	if (!ker.bKeyDown)
	{
		return;
	}

	game.playMusic();

}

void quit(KEY_EVENT_RECORD ker)
{
	if (!ker.bKeyDown)
	{
		return;
	}

	game.quit();
}