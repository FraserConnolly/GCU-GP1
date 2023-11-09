#include "GameSelectionMenu.h"
#include <iostream>
using namespace std;

GameSelectionMenu::MenuOption GameSelectionMenu::GetMenuSelection()
{
	int input;
	MenuOption choice;
	bool validChoice = false;

	system("cls");
	cout << "Welcome to Fraser Connolly's fantastic console games!" << std::endl;
	cout << std::endl;
	
	while (!validChoice)
	{
		cout << "1\tSpace Invaders" << std::endl;
		cout << "2\tParanoid"		<< std::endl;
		cout << "---------------"	<< std::endl;
		cout << "0\tQuit"			<< std::endl;

		try
		{
			cin >> input;
			if (cin.fail())
			{
				input = -1;
				cin.clear();  // clears the fault flag
				cin.ignore(); // remove any existing data in the input buffer
			}
		}
		catch (const std::exception&)
		{
			input = -1;
		}
	
		validChoice = input >= 0 && input <= 2;

		if (!validChoice)
		{
			system("cls");
			cout << "Invalid choice, please select from the below list." << std::endl;
			cout << std::endl;
		}
	}

	choice = static_cast<MenuOption>(input);

	return choice;
}
