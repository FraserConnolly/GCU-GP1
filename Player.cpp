#include "AliensGameSource.h"
#include "Player.h"

#define PLAYER_SPEED 25
#define LASER_SPEED 40

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

	float movement = 0;

	if ( leftInputPressed )
	{
		movement = PLAYER_SPEED * game->getDeltaTime() * -1;
		//translateByGridUnit ( -1, 0 );
	}
	else if ( rightInputPressed )
	{
		movement = PLAYER_SPEED * game->getDeltaTime() * 1;
		//translateByGridUnit ( 1, 0 );
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

	if ( game->getGameTime() > m_lastFireTime + fireTimeout )
	{
		auto laser = game->getAvilableLaser ( );

		if ( laser == nullptr )
		{
			// no available lasers
			return;
		}

		// can fire
		m_lastFireTime = game->getGameTime();

		Vector2Int startPosition;
		startPosition.X = getGridX ( ) + 2;
		startPosition.Y = getGridY ( ) - 1;

		laser->launch ( startPosition, LASER_SPEED );
	}
	
}
