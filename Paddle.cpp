#include "ParanoidGameSource.h"
#include "Paddle.h"

void Paddle::tick(ParanoidGameSource* game)
{
	processMovement(game);
	processInput(game);
}

void Paddle::applyPowerUp(const POWER_UP_TYPE type)
{
	// to do
}

void Paddle::resetPowerUps()
{
	// to do
}

void Paddle::processMovement(ParanoidGameSource* game)
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

void Paddle::processInput(ParanoidGameSource* game)
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
