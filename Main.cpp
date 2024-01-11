/*
* Created By: Fraser Connolly
* Created Date: 2023-09-28
* 2023-09-11 Added menu system
*/

// set this to skip the menu and play a specific game.
//#define SPACE_INVADERS
//#define PARANOID

#include <stack>
#if defined SPACE_INVADERS
#include "SpaceInvaderMainScene.h"
#elif defined PARANOID
#include "ParanoidGameMainScene.h"
#else
#include "Menu.h"
#endif

int main ( )
{
	std::stack<std::shared_ptr<GameScene>> scenes;

	// clear the screen
	system("cls");

	int lastGameSceneResponse = 0;

#if defined SPACE_INVADERS
	scenes.push ( std::make_shared<SpaceInvaderMainScene> ( ) );
#elif defined PARANOID
	scenes.push ( std::make_shared<ParanoidGameMainScene> ( ) );
#else
	scenes.push ( std::make_shared<Menu> ( ) );
#endif

	while ( ! scenes.empty() )
	{
		std::shared_ptr<GameScene> game = scenes.top ( );

		if ( game == nullptr )
		{
			scenes.pop ( );
			continue;
		}

		game -> initaliseGame ( lastGameSceneResponse );
		game -> gameLoop ( );

		std::shared_ptr<GameScene> newScene = nullptr;
		bool loadAdditively = false;
		lastGameSceneResponse = game -> loadNextScene ( newScene, loadAdditively );

		if ( ! loadAdditively )
		{
			scenes.pop ( );
		}

		scenes.push ( newScene );
	}
	
	return 0;
}
