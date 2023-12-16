#include "ParanoidGameSource.h"
#include "Paddle.h"

void Paddle::tick(ParanoidGameSource * const game)
{
	if ( m_powerUpApplied && game->getGameTime ( ) > m_powerUpResetTime )
	{
		resetPowerUps ( );
	}

	processMovement(game);
	processInput(game);
}

void Paddle::applyPowerUp(const POWER_UP_TYPE type, ParanoidGameSource * const game )
{
	switch ( type )
	{
		case POWER_UP_TYPE::PADDLE_DECREASE:
			resizePaddle( PADDLE_WIDTH_SMALL );
			break;

		case POWER_UP_TYPE::PADDLE_INCREASE:
			resizePaddle ( PADDLE_WIDTH_LARGE );
			break;

		case POWER_UP_TYPE::PADDLE_SPEED_DECREASE:
			m_speed = PADDLE_SPEED - ( PADDLE_SPEED * PADDLE_SPEED_POWER_UP_MULTIPLYER );
			break;
		
		case POWER_UP_TYPE::PADDLE_SPEED_INCREASE:
			m_speed = PADDLE_SPEED + ( PADDLE_SPEED * PADDLE_SPEED_POWER_UP_MULTIPLYER );
			break;

		default:
			return;
	}

	m_powerUpApplied = true;
	m_powerUpResetTime = game->getGameTime ( ) + POWER_UP_DURATION;

	// prevent the player going off the edge of the screen
	if ( getGridX ( ) + getWidth ( ) >= ( unsigned int ) game->getScreenWidth ( ) )
	{
		setGridX ( game->getScreenWidth ( ) - m_width );
	}
	else if ( getGridX ( ) < 0 )
	{
		setGridX ( 0 );
	}
}

void Paddle::resetPowerUps()
{
	m_powerUpApplied = false;
	resizePaddle ( PADDLE_WIDTH_NORMAL );
	m_speed = PADDLE_SPEED;
}

void Paddle::processMovement(ParanoidGameSource * const game)
{
	bool leftInputPressed = game->m_keyboardInput.isPressed(VK_LEFT);
	bool rightInputPressed = game->m_keyboardInput.isPressed(VK_RIGHT);

	if (leftInputPressed && rightInputPressed)
	{
		return;
	}

	float horivontalMovement = 0;

	if (leftInputPressed)
	{
		horivontalMovement = m_speed * game->getDeltaTime() * -1;
		//translateByGridUnit ( -1, 0 );
	}
	else if (rightInputPressed)
	{
		horivontalMovement = m_speed * game->getDeltaTime() * 1;
		//translateByGridUnit ( 1, 0 );
	}

	translate(horivontalMovement, 0);

	// prevent the player going off the edge of the screen
	if (getGridX() + getWidth() >= (unsigned int) game->getScreenWidth())
	{
		setGridX(game->getScreenWidth() - m_width);
	}
	else if (getGridX() < 0)
	{
		setGridX(0);
	}

}

void Paddle::processInput(ParanoidGameSource * const game)
{
	if (game->getHasStarted())
	{
		return;
	}

	bool spaceInputPressed = game->m_keyboardInput.isPressed(VK_SPACE);

	if (spaceInputPressed)
	{
		// start level
		game->startLevel();
	}
}

void Paddle::resizePaddle ( unsigned int newSize )
{ 
	if ( m_width == newSize )
	{
		return;
	}

	// cap the size of the paddle.
	if ( newSize == 0 )
	{
		newSize = 1;
	}
	else if ( newSize > PADDLE_WIDTH_LARGE )
	{
		newSize = PADDLE_WIDTH_LARGE;
	}

	// calculate how far the paddle must move to maintain the same centre point.
	int changeInSize = m_width - newSize;
	float changeInX = changeInSize / 2.0;
	translate ( changeInX, 0 );

	// apply the new size
	m_width = newSize;
}
