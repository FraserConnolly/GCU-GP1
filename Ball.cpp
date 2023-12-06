#include "Ball.h"
#include "GameSource.h"
#include "Ground.h"
#include "Block.h"
#include "Paddle.h"

void Ball::onCollision(const GameObject& collision, const Point collisionPoint)
{
	// check if the ball collided with a block or with the ground.

	const Ground * ground = dynamic_cast<const Ground*>(&collision);

	if (ground != nullptr)
	{
		setActive(false);
		return;
	}

	const Block* block = dynamic_cast<const Block*>(&collision);

	if (block != nullptr)
	{
		// collided with a block

		if (m_penetrate)
		{
			// continue through the block
		}
		else
		{
			// change direction
			applyChangeOfDirection(collisionPoint);
		}
		return;
	}

	const GameObject* paddle = dynamic_cast<const Paddle*>(&collision);

	if (paddle != nullptr)
	{
		applyChangeOfDirection(collisionPoint);
	}
}

// Projectiles implementation of tick will deactivate a projectile if it goes off screen.
// But for the ball we want it to bounce of the top and sides of the screen.
void Ball::tick(GameSource* game)
{
	if (!m_active)
	{
		return;
	}

	m_previousGridPosition.X = getGridX();
	m_previousGridPosition.Y = getGridY();

	translate(m_speed * game->deltaTime * m_xDirection, m_speed * game->deltaTime * m_yDirection);

	if (getGridY() < 0)
	{
		// hit the top of the screen
		applyChangeOfDirection(Point(getGridX(), 0));
		return;
	}

	if (getGridY() >= game->getScreenHeight())
	{
		// shouldn't happen as the ground should have been collided with first.
		setActive(false);
		return;
	}

	if (getGridX() < 0)
	{
		// hit the left edge of the screen
		applyChangeOfDirection(Point(0, getGridY()));
		return;
	}

	if (getGridX() >= game->getScreenWidth())
	{
		// hit the right edge of the screen
		applyChangeOfDirection(Point(game->getScreenWidth() - 1, getGridY()));
		return;
	}
}

void Ball::applyChangeOfDirection(const Point collissionPoint)
{
	// get current direction
	float xDirection = m_xDirection;
	float yDirection = m_yDirection;

	// to do calculate normal based on the side of the block that was hit

	// apply new direction
	setDirection(xDirection, yDirection);

}

