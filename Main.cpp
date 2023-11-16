/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
*/

#include "GameSource.cpp"

GameSource game;

void quit(KEY_EVENT_RECORD);
void spacebarPressed(KEY_EVENT_RECORD ker);

int main()
{
	GameSource game;
	game.initaliseGame();

	game.kInput.registerOnKey(VK_SPACE, spacebarPressed);
	game.kInput.registerOnKey(VK_ESCAPE, quit);
	game.gameLoop();

	return 0;
}

bool white;

void spacebarPressed(KEY_EVENT_RECORD ker)
{
	if (!ker.bKeyDown)
	{
		return;
	}

	if (white)
	{
		game.renderer.setBackgroundColour(0x00, 0x00, 0x00);
	}
	else
	{
		game.renderer.setBackgroundColour(0xff, 0xff, 0xff);
	}

	white = !white;
}

void quit(KEY_EVENT_RECORD ker)
{
	game.quit();
}