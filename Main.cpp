/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
* 2023-09-11 Added menu system
*/

// set this to skip the menu and play a specific game.
//#define TestGame SPACE_INVADERS
#define TestGame PARANOID

#include "GameSelectionMenu.h"
#include "AliensGameSource.h"
#include "ParanoidGameSource.h"

void fontTest ( );

int main ( )
{
	std::unique_ptr<GameSource> game;

	system("cls");

#ifndef TestGame
	for ( ; ; )
	{
		GameSelectionMenu menu;
		GameSelectionMenu::MenuOption selection = menu.GetMenuSelection();
#else
		GameSelectionMenu::MenuOption selection = GameSelectionMenu::TestGame;
#endif // !TestGame

		switch (selection)
		{
			case GameSelectionMenu::QUIT:
				return 0;
			case GameSelectionMenu::SPACE_INVADERS:
				game = std::make_unique<AliensGameSource>();
				break;
			case GameSelectionMenu::PARANOID:
				game = std::make_unique<ParanoidGameSource>();
				break;
			default:
				return -2; // unknown menu selection
		}

		game -> initaliseGame ( );
		game -> gameLoop ( );

		// the game has finished so clear the pointer so the destructors can run.
		game.reset( );

#ifndef TestGame
}
#endif // !TestGame
	
	return 0;
}

void fontTest ( )
{
	CONSOLE_FONT_INFO lpConsoleCurrentFont;
	auto result = GetCurrentConsoleFont ( GetStdHandle ( STD_OUTPUT_HANDLE ), false, &lpConsoleCurrentFont );

	if ( result )
	{
		cout << "Font: " << lpConsoleCurrentFont.dwFontSize.X << ", " << lpConsoleCurrentFont.dwFontSize.Y << endl;
	}
}