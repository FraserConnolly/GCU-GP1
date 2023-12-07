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
			// if the point of collision is the left or right most cell of the block
			// then consider this a side hit

			if (collisionPoint.X == block->getGridX() || collisionPoint.X == block->getGridX() + block->getWidth())
			{
				applyChangeOfDirection(Edge::RIGHT);
			}
			else
			{
				applyChangeOfDirection(Edge::TOP);
			}

		}
		return;
	}

	const GameObject* paddle = dynamic_cast<const Paddle*>(&collision);

	if (paddle != nullptr)
	{
		applyChangeOfDirection(Edge::BOTTOM);
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

	Point screenSize(
		game->getScreenWidth()-1,
		game->getScreenHeight()-1
	);

	if (getGridY() < 0)
	{
		// hit the top of the screen
		setGridY(0);
		applyChangeOfDirection(Edge::TOP);
		return;
	}

	if (getGridY() > screenSize.Y)
	{
		// shouldn't happen as the ground should have been collided with first.
		setGridY(screenSize.Y);
		setActive(false);
		return;
	}

	if (getGridX() < 0)
	{
		// hit the left edge of the screen
		setGridX(0);
		applyChangeOfDirection(Edge::LEFT);
		return;
	}

	if (getGridX() > screenSize.X)
	{
		// hit the right edge of the screen
		setGridX(screenSize.X);
		applyChangeOfDirection(Edge::RIGHT);
		return;
	}
}

void Ball::applyChangeOfDirection(const Edge edge)
{
	// get current direction
	Point direction(m_xDirection, m_yDirection);

	switch (edge)
	{
	case Edge::BOTTOM:
	case Edge::TOP:
		direction.Y *= -1;
		break;
	case Edge::LEFT:
	case Edge::RIGHT:
		direction.X *= -1;
		break;
	}

	// apply new direction
	setDirection(direction.X, direction.Y);

	// To prevent multiple collisions without ball appearing to move
	// force the ball to move by one grid unit.
	// to do, this requires more testing.

	Point movement(0, 0);
	if (direction.X > 0)
	{
		movement.X = 1;
	}
	else if (direction.X < 0)
	{
		movement.X = -1;
	}

	if (direction.Y > 0)
	{
		movement.Y = 1;
	}
	else if (direction.Y < 0)
	{
		movement.Y = -1;
	}

	translateByGridUnit(movement.X, movement.Y);
}
