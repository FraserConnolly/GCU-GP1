#pragma once
#include "GameScene.h"
#include "Button.h"

class Menu :
    public GameScene
{ 

public:
    Menu ( ) { }

    void initaliseGame ( int lastGameSceneResponse ) override;
    int loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively ) override;

protected:

    void initaliseLevel ( ) override;
    void updateGame ( ) override;
    void drawGame ( ) override;
    

private:

    float splashScreenTimer = 2.5f;
    bool showSplashScreen = true;
    int m_highlightOption = 0;
    int m_selectedOption = 0;

    Button m_btnSpaceInvader;
    Button m_btnParanoid;
    Button m_btnPortfolio;
    Button m_btnExit;

    void processSplashScreen ( );
    void processMenu ( );

};

