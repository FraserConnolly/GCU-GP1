#include "Menu.h"
#include "SpaceInvaderMainScene.h"
#include "ParanoidGameMainScene.h"
#include "Resources.h"

#define OPTION_COUNT 4

void Menu::initaliseGame ( int lastGameSceneResponse )
{ 
	GameScene::initaliseGame ( lastGameSceneResponse );

	m_highlightOption = 1;
	m_selectedOption = 0;

	m_keyboardInput.registerKey ( VK_UP );
	m_keyboardInput.registerKey ( VK_DOWN );
	m_keyboardInput.registerKey ( VK_SPACE );
	m_keyboardInput.registerKey ( VK_RETURN );
	m_keyboardInput.registerKey ( '1' );
	m_keyboardInput.registerKey ( '2' );
	m_keyboardInput.registerKey ( '3' );
	m_keyboardInput.registerKey ( '4' );

	m_btnSpaceInvader.setColours ( ( CellColour ) ( CellColour::Back_Black | CellColour::Fore_Red ), ( CellColour ) ( CellColour::Back_Red | CellColour::Fore_Black ) );
	m_btnSpaceInvader.setGridPosition ( 24, 12 );
	m_btnSpaceInvader.setCharacters ( spaceInvadorsTextData, spaceInvadorsTextDataCols, asciiArtShadowRows, 2, 1 );
	
	m_btnParanoid    .setColours ( ( CellColour ) ( CellColour::Back_Black | CellColour::Fore_Yellow ), ( CellColour ) ( CellColour::Back_Yellow | CellColour::Fore_Black ) );
	m_btnParanoid    .setGridPosition ( 24, m_btnSpaceInvader.getGridY() + m_btnSpaceInvader.getHeight() + 1 );
	m_btnParanoid    .setCharacters ( paranoidTextData, paranoidTextDataCols, asciiArtShadowRows, 24, 1 );

	m_btnPortfolio   .setColours ( ( CellColour ) ( CellColour::Back_Black | CellColour::Fore_Green ), ( CellColour ) ( CellColour::Back_Green | CellColour::Fore_Black ) );
	m_btnPortfolio   .setGridPosition ( 24, m_btnParanoid.getGridY ( ) + m_btnParanoid.getHeight ( ) + 1 );
	m_btnPortfolio   .setCharacters ( portfolioTextData, portfolioTextDataCols, asciiArtShadowRows, 19, 1 );

	m_btnExit        .setColours ( ( CellColour ) ( CellColour::Back_Black | CellColour::Fore_Magenta ), ( CellColour ) ( CellColour::Back_Magenta | CellColour::Fore_Black ) );
	m_btnExit        .setGridPosition ( 24, m_btnPortfolio.getGridY ( ) + m_btnPortfolio.getHeight ( ) + 1 );
	m_btnExit        .setCharacters ( exitTextData, exitTextDataCols, asciiArtShadowRows, 41, 1 );
}

int Menu::loadNextScene ( std::shared_ptr<GameScene> &newScene, bool & loadAdditively )
{
	switch ( m_selectedOption )
	{
		case 1:
			newScene = std::make_shared<SpaceInvaderMainScene> ( );
			loadAdditively = true;
			break;

		case 2:
			newScene = std::make_shared<ParanoidGameMainScene> ( );
			loadAdditively = true;
			break;

		case 3:
			newScene = std::make_shared<Menu> ( );
			loadAdditively = false;
			break;

		default:
		case 4:
			newScene = nullptr;
			loadAdditively = false;
			break;
	}

	return 0;
}

void Menu::initaliseLevel ( )
{ 
}

void Menu::updateGame ( )
{ 
	if ( showSplashScreen )
	{
		processSplashScreen ( );
		return;
	}

	processMenu ( );

	m_btnSpaceInvader.setSelectionStatus ( m_highlightOption == 1 );
	m_btnParanoid.setSelectionStatus ( m_highlightOption == 2 );
	m_btnPortfolio.setSelectionStatus ( m_highlightOption == 3 );
	m_btnExit.setSelectionStatus ( m_highlightOption == 4 );
}

void Menu::drawGame ( )
{ 
	if ( showSplashScreen )
	{
		for ( size_t x = 0; x < getScreenWidth ( ); x++ )
		{
			for ( size_t y = 0; y < getScreenHeight ( ); y++ )
			{
				m_backBuffer->setChar ( x, y, spashScreenData [ x + y * getScreenWidth ( ) ] );
			}
		}
		
		return ;
	}

	for ( size_t x = 0; x < getScreenWidth ( ); x++ )
	{
		for ( size_t y = 0; y < getScreenHeight ( ); y++ )
		{
			m_backBuffer->setChar ( x, y, menuScreenData [ x + y * getScreenWidth ( ) ] );
		}
	}

	drawGameObject ( m_btnSpaceInvader );
	drawGameObject ( m_btnParanoid );
	drawGameObject ( m_btnPortfolio );
	drawGameObject ( m_btnExit );
}

void Menu::processSplashScreen ( )
{
	if ( splashScreenTimer > 0 )
	{
		splashScreenTimer -= GameScene::getDeltaTime ( );
	}
	else
	{
		showSplashScreen = false;
		m_btnSpaceInvader.setActive ( true );
		m_btnParanoid.setActive ( true );
		m_btnPortfolio.setActive ( true );
		m_btnExit.setActive ( true );
		m_highlightOption = 1;
	}
}

void Menu::processMenu ( )
{ 
	// Select Space Invaders
	if ( m_keyboardInput.wasPressedThisFrame ( '1' ) )
	{
		m_highlightOption = 1;
		m_runLoop = false;
		return;
	}
	
	// Select Paranoid
	if ( m_keyboardInput.wasPressedThisFrame ( '2' ) )
	{
		m_highlightOption = 2;
		m_runLoop = false;
		return;
	}

	// Select Portfolio
	if ( m_keyboardInput.wasPressedThisFrame ( '3' ) )
	{
		m_highlightOption = 3;
		ShellExecuteA ( nullptr, "open", "https://fraserconnolly.co.uk", nullptr, nullptr, SW_SHOWNORMAL );
		return;
	}

	// Select Exit
	if ( m_keyboardInput.wasPressedThisFrame ( '4' ) )
	{
		m_highlightOption = 4;
		m_runLoop = false;
		return;
	}

	if ( m_keyboardInput.wasPressedThisFrame ( VK_DOWN ) )
	{
		m_highlightOption++;
	}

	if ( m_keyboardInput.wasPressedThisFrame ( VK_UP ) )
	{
		m_highlightOption--;
	}

	if ( m_highlightOption < 1 )
	{
		m_highlightOption = OPTION_COUNT;
	}
	else if ( m_highlightOption > OPTION_COUNT )
	{
		m_highlightOption = 1;
	}
	
	if ( m_keyboardInput.wasPressedThisFrame ( VK_RETURN ) || m_keyboardInput.wasPressedThisFrame (VK_SPACE) )
	{
		if ( m_highlightOption == 3 )
		{
			return;
		}

		m_selectedOption = m_highlightOption;
		m_runLoop = false;
	}

}

