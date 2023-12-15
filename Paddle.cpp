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
			m_width = PADDLE_WIDTH_SMALL;
			break;

		case POWER_UP_TYPE::PADDLE_INCREASE:
			m_width = PADDLE_WIDTH_LARGE;
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
}

void Paddle::resetPowerUps()
{
	m_powerUpApplied = false;
	m_width = PADDLE_WIDTH_NORMAL;
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

	const float speedMultiplyer = 40;
	float horivontalMovement = 0;

	if (leftInputPressed)
	{
		horivontalMovement = speedMultiplyer * game->getDeltaTime() * -1;
		//translateByGridUnit ( -1, 0 );
	}
	else if (rightInputPressed)
	{
		horivontalMovement = speedMultiplyer * game->getDeltaTime() * 1;
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
