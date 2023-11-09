#pragma once
class GameSelectionMenu
{
public:

	enum MenuOption
	{
		QUIT,
		SPACE_INVADERS,
		PARANOID
	};

	MenuOption GetMenuSelection();

};

