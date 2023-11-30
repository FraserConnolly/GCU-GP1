#include "AliensGameSource.h"
#include "Player.h"

void Player::tick ( AliensGameSource * game )
{
	processMovement ( game );
	processCombat   ( game );
}

void Player::processMovement ( AliensGameSource * game )
{ 
	bool leftInputPressed  = game->m_keyboardInput.isPressed ( VK_LEFT );
	bool rightInputPressed = game->m_keyboardInput.isPressed ( VK_RIGHT );

	if ( leftInputPressed && rightInputPressed )
	{
		return;
	}

	const float speedMultiplyer = 100;
	float movement = 0;

	if ( leftInputPressed )
	{
		movement = speedMultiplyer * game->deltaTime * -1;
	}
	else if ( rightInputPressed )
	{
		movement = speedMultiplyer * game->deltaTime * 1;
	}

	translate ( movement, 0 );

	// prevent the player going off the edge of the screen
	if ( getGridX ( ) >= game->getScreenWidth ( ) )
	{
		setGridX ( game->getScreenWidth ( ) - 1 );
	}
	else if ( getGridX ( ) < 0 )
	{
		setGridX ( 0 );
	}
}

void Player::processCombat ( AliensGameSource * game )
{
	bool fireInputPressed = game->m_keyboardInput.isPressed ( VK_RCONTROL );

	if ( ! fireInputPressed )
	{
		return;
	}

	// player trying to fire weapon.

	if ( game->gameTime > m_lastFireTime + fireTimeout )
	{
		auto laser = game->getAvilableLaser ( );

		if ( laser == nullptr )
		{
			// no available lasers
			return;
		}

		// can fire
		m_lastFireTime = game->gameTime;

		COORD startPosition;
		startPosition.X = getGridX ( );
		startPosition.Y = getGridY ( ) - 1;

		laser->launch ( startPosition, 200 );
	}
	
}
