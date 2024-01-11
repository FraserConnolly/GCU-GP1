#pragma once
#include "GameScene.h"
#include "Button.h"
#include "UiText.h"

#define OPTION_COUNT 2

class HighScoreScene : public GameScene
{ 
public:

	HighScoreScene ( ) :
		m_lblHighScore ( "Score", 10 ),
		m_lblHighScoreValue ( "%i", 25 )
	{ }

	void initaliseGame ( int lastGameSceneResponse ) override;
	int loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively ) override;

	void setGameLabel ( const wchar_t * gameLabelData, const size_t cols, const size_t rows, const CellColour colour );
	void setScore ( int score );

protected:

	void initaliseLevel ( ) override;
	void updateGame ( ) override;
	void drawGame ( ) override;

private:

	int m_selectedOption = 2;
	int m_highlightOption = 1;

	Button m_btnGameOver;
	Button m_btnGame;
	Button m_btnRetry;
	Button m_btnExit;
	UiText m_lblHighScore;
	UiText m_lblHighScoreValue;

	void processMenu ( );
};

