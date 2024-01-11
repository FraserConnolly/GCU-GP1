#include "HighScoreScene.h"
#include "Resources.h"

void HighScoreScene::initaliseGame ( int lastGameSceneResponse )
{ 
	GameScene::initaliseGame ( lastGameSceneResponse );

	m_keyboardInput.registerKey ( VK_LEFT );
	m_keyboardInput.registerKey ( VK_RIGHT );
	m_keyboardInput.registerKey ( VK_SPACE );
	m_keyboardInput.registerKey ( VK_RETURN );

	m_btnGameOver.setColours ( CellColour::Fore_Red, CellColour::Fore_Red );
	m_btnGameOver.setCharacters ( gameOverTextData, gameOversTextDataCols, asciiArtBloodyRows );
	m_btnGameOver.setGridPosition ( ( getScreenWidth ( ) / 2 ) - ( m_btnGameOver.getWidth ( ) / 2 ), 4 );
	m_btnGameOver.setActive ( true );

	m_lblHighScore.updateText ( );
	m_lblHighScore.setGridPosition ( ( getScreenWidth() / 2 ) - ( m_lblHighScore.getWidth( ) / 2 ), 26 );
	
	m_lblHighScoreValue.setGridPosition ( ( getScreenWidth ( ) / 2 ) - ( m_lblHighScoreValue.getWidth ( ) / 2 ), 28 );

	m_btnRetry.setCharacters ( retryTextData, retryTextDataCols, asciiArtShadowRows, 2, 2 );
	m_btnRetry.setGridPosition ( 35, 35 );
	m_btnRetry.setActive ( true );

	m_btnExit.setCharacters ( exitTextData, exitTextDataCols, asciiArtShadowRows, 2, 2 );
	m_btnExit.setGridPosition ( 95, 35 );
	m_btnExit.setActive ( true );

	m_btnGame.setGridPosition ( ( getScreenWidth ( ) / 2 ) - ( m_btnGame.getWidth ( ) / 2 ), 18 );

	m_highlightOption = 1;
}

int HighScoreScene::loadNextScene ( std::shared_ptr<GameScene>&newScene, bool & loadAdditively )
{
	if ( m_selectedOption == 1 )
	{
		// retry
		return 0;
	}
	
	return -1;
}

void HighScoreScene::setGameLabel ( const wchar_t * gameLabelData, const size_t cols, const size_t rows, const CellColour colour )
{
	m_btnGame.setColours ( colour, colour );
	m_btnGame.setCharacters ( gameLabelData, cols, rows );
	m_btnGame.setActive ( true );
}

void HighScoreScene::setScore ( int score )
{ 
	m_lblHighScoreValue.updateText ( score );
}

void HighScoreScene::initaliseLevel ( ) { }

void HighScoreScene::updateGame ( )
{ 
	processMenu ( );

	m_btnRetry.setSelectionStatus ( m_highlightOption == 1 );
	m_btnExit.setSelectionStatus ( m_highlightOption == 2 );
}

void HighScoreScene::processMenu ( )
{
	if ( m_keyboardInput.wasPressedThisFrame ( VK_RIGHT ) )
	{
		m_highlightOption++;
	}

	if ( m_keyboardInput.wasPressedThisFrame ( VK_LEFT ) )
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

	if ( m_keyboardInput.wasPressedThisFrame ( VK_RETURN ) || m_keyboardInput.wasPressedThisFrame ( VK_SPACE ) )
	{
		switch ( m_highlightOption )
		{
			case 1:
				m_selectedOption = 1;
				break;
			case 2:
			default:
				m_selectedOption = 2;
				break;
		}
		m_runLoop = false;
	}
}

void HighScoreScene::drawGame ( )
{ 

	drawGameObject ( m_btnGameOver );
	drawGameObject ( m_btnGame );
	drawGameObject ( m_btnRetry );
	drawGameObject ( m_btnExit );
	drawGameObject ( m_lblHighScore );
	drawGameObject ( m_lblHighScoreValue );

}
