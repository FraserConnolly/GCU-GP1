#pragma once
#include <iostream>
#include <string>
#include "Window.h"
#include "FrameTimer.h"
#include "KeyboardInput.h"
#include "MusicPlayer.h"
#include "ScreenBuffer.h"

class GameObject;

class GameScene
{
public:
	GameScene()
		: m_stdWindow(GetStdHandle(STD_OUTPUT_HANDLE))
	{ };

	virtual ~GameScene()
	{
		delete m_backBuffer;
		delete m_frontBuffer;

		// restore the screen buffer to the standard output.
		SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
	}

	virtual void initaliseGame ( int lastGameSceneResponse );
	void gameLoop ( );
	virtual int loadNextScene ( std::shared_ptr<GameScene> & newScene, bool & loadAdditively ) = 0;
	void quit ( );

	KeyboardInput m_keyboardInput;

	/// <summary>
	/// The length of time in seconds that the game has been running for.
	/// </summary>
	inline const float getGameTime() const
	{
		return m_gameTime;
	}

	/// <summary>
	/// The length of time in seconds that the previous frame took to be completed.
	/// </summary>
	inline const float getDeltaTime() const
	{
		return m_deltaTime;
	}

	/// <summary>
	/// The length of time in milliseconds that the previous frame took to be completed.
	/// </summary>
	inline const float getDeltaTimeMs() const
	{
		return m_deltaTimeMs;
	}

	inline const int getScreenWidth ( ) const
	{
		return m_stdWindow.getWidth ( );
	}

	inline const int getScreenHeight ( ) const
	{
		return m_stdWindow.getHeight ( );
	}

	inline const int getFrameCount() const
	{
		return m_frameCount;
	}

protected:
	
	virtual void initaliseLevel() = 0;
	virtual void processInput ( );
	virtual void updateGame ( );
	virtual void drawGame ( ) = 0;

	/// <summary>
	/// Helper method that takes in the pointer to an array of GameObjects
	/// and the number of objects in the array.
	/// Each active object is then rendered to the back buffer.
	/// </summary>
	template< class GameObject >
	void drawObjectsInArray ( GameObject * objects, size_t count )
	{
		for ( int i = 0; i < count; i++ )
		{
			GameObject & gObject = objects [ i ];

			if ( !gObject.getActive ( ) )
			{
				continue;
			}

			drawGameObject ( gObject );
		}
	}

	void drawGameObject ( const GameObject & object );

	bool m_runLoop = false;
	FrameTimer m_frameTimer;
	MusicPlayer m_musicPlayer;

	/// <summary>
	/// This screen buffer pointed to by m_backBuffer 
	/// will never be the active console buffer.
	/// </summary>
	ScreenBuffer* m_backBuffer = nullptr;

private:
	
	void renderFrame ( );
	void quitKeyPressed ( );
	
	/// <summary>
	/// The length of time in seconds that the game has been running for.
	/// </summary>
	float m_gameTime = 0;

	/// <summary>
	/// The length of time in seconds that the previous frame took to be completed.
	/// </summary>
	float m_deltaTime = 0;

	/// <summary>
	/// The length of time in milliseconds that the previous frame took to be completed.
	/// </summary>
	float m_deltaTimeMs = 0;
	int m_frameCount = 0;
	
	bool isInitialised = false;

	ScreenBuffer* m_frontBuffer = nullptr;
	Window m_stdWindow;
};

