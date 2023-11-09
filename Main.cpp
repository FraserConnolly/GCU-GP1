/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
* 2023-09-11 Added menu system
*/

#include "GameSelectionMenu.h"
#include "AliensGameSource.h"

int main ( )
{
	GameSelectionMenu menu;
	std::unique_ptr<GameSource> game;

	for ( ; ; )
	{
		auto selection = menu.GetMenuSelection();

		switch (selection)
		{
			case GameSelectionMenu::QUIT:
				return 0;
			case GameSelectionMenu::SPACE_INVADERS:
				game = std::make_unique<AliensGameSource>();
				break;
			case GameSelectionMenu::PARANOID:
				return -1; // game not implemented
			default:
				return -2; // unknwon menu selection
		}

		game -> initaliseGame ( );
		game -> gameLoop ( );

		// the game has finished so clear the pointer so the destructors can run.
		game.reset( );
	}

	return 0;
}
