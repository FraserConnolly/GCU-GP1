#include "Ball.h"
#include "GameSource.h"
#include "Ground.h"
#include "Block.h"
#include "Paddle.h"
#include "ParanoidGameSource.h"

//#define USE_BALL_DEBUG_VISUAL

#define PADDLE_RETURN_ANGLE_MAX 65

void Ball::onCollision(const GameObject& collision, const Vector2Int & collisionPoint)
{
	Vector2Int translation;

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

			if ( block->isCorner ( collisionPoint ) )
			{
				applyChangeOfDirection ( Edge::CORNER );
			}
			else if ( block->getGridX ( ) == collisionPoint.X || block->getGridX ( ) + block->getWidth ( ) - 1 == collisionPoint.X )
			{
				applyChangeOfDirection ( Edge::VERTICAL_EDGE );
			}
			else if ( block->getGridY ( ) == collisionPoint.Y || block->getGridY ( ) + block->getHeight ( ) - 1 == collisionPoint.Y )
			{
				applyChangeOfDirection ( Edge::HORIZONTAL_EDGE );
			}
			else
			{
				// collisionPoint must be a center piece of the block.
				// This should never happen, but in this event we will send the ball back in the
				// direction that it came.
				applyChangeOfDirection ( Edge::RETURN );
			}


			// force the ball to move by a grid unit to prevent duplicate collisions.
			if (m_direction.X > 0)
			{
				translation.X = 1;
			}
			else if (m_direction.X < 0)
			{
				translation.X = -1;
			}

			if (m_direction.Y > 0)
			{
				translation.Y = 1;
			}
			else if (m_direction.Y < 0)
			{
				translation.Y = -1;
			}

			translateByGridUnit(translation);

		}
		return;
	}

	const GameObject* paddle = dynamic_cast<const Paddle*>(&collision);

	if (paddle != nullptr)
	{
		float returnAngle = calculatePaddleReturnAngle ( *paddle, collisionPoint );
		setDirection ( -1, 0 );
		rotate ( returnAngle );

		if ( m_direction.Y > 0 )
		{
			m_direction.Y *= -1;
		}

		m_direction.normalise ( );

		// force the ball to move up by one.
		translation.Y = - 1;
		translateByGridUnit(translation);
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

	if ( m_powerUpApplied && game->getGameTime ( ) > m_powerUpResetTime )
	{
		resetPowerUps ( );
	}

	auto gridPosition = getGridPosition();

	m_previousGridPosition.X = getGridX();
	m_previousGridPosition.Y = getGridY();

	translate ( m_direction * m_speed * game->getDeltaTime ( ) );

	// check if the ball has gone out of bounds

	Vector2Int screenSize(
		game->getScreenWidth() - 1,
		game->getScreenHeight() - 1
	);

	if (getY() < 0)
	{
		// hit the top of the screen
		setGridY(1);
		applyChangeOfDirection(Edge::HORIZONTAL_EDGE);
	}
	else if (getGridY() > screenSize.Y)
	{
		// shouldn't happen as the ground should have been collided with first.
		setActive(false);
	}
	else if (getGridX() < 0)
	{
		// hit the left edge of the screen
		setGridX(1);
		applyChangeOfDirection(Edge::VERTICAL_EDGE);
	}
	else if (getGridX() > screenSize.X)
	{
		// hit the right edge of the screen
		setGridX(screenSize.X - 1);
		applyChangeOfDirection(Edge::VERTICAL_EDGE);
		return;
	}

	if (gridPosition != getGridPosition())
	{
		// only update the previous grid position if our grid position has changed this frame.
		m_previousGridPosition = gridPosition;
	}

#ifdef USE_BALL_DEBUG_VISUAL
	if (m_xDirection > 0 && m_yDirection > 0)
	{
		// bottom right
		m_symbol[0].UnicodeChar = 0x251B;
	}
	else if (m_xDirection < 0 && m_yDirection < 0)
	{
		// top left
		m_symbol[0].UnicodeChar = 0x250F;
	}
	if (m_xDirection > 0 && m_yDirection < 0)
	{
		// top right
		m_symbol[0].UnicodeChar = 0x2513;
	}
	else if (m_xDirection < 0 && m_yDirection > 0)
	{
		// bottom left
		m_symbol[0].UnicodeChar = 0x2517;
	}
#endif
}

void Ball::applyPowerUp ( const POWER_UP_TYPE type, ParanoidGameSource * const game )
{
	switch ( type )
	{
		case POWER_UP_TYPE::BALL_PENETRATE:
			m_penetrate = true;
			break;
		default:
			return;
	}

	m_powerUpApplied = true;
	m_symbol [ 0 ].UnicodeChar = BALL_SYMBOL_PENETRATE;
	m_powerUpResetTime = game->getGameTime ( ) + POWER_UP_PENETRATION_DURATION;
}

void Ball::resetPowerUps ( )
{ 
	m_symbol [ 0 ].UnicodeChar = BALL_SYMBOL_NORMAL;
	m_penetrate = false;
	m_powerUpApplied = false;
}



void Ball::applyChangeOfDirection(const Edge edge)
{
	// get current direction
	Vector2 direction = getDirection ( );
	auto gridPosition = getGridPosition();

	switch (edge)
	{
	case Edge::CORNER:
		if (m_previousGridPosition.X != gridPosition.X)
		{
			direction.X *= -1;
		}

		if (m_previousGridPosition.Y != gridPosition.Y)
		{
			direction.Y *= -1;
		}
		break;
	case Edge::HORIZONTAL_EDGE:
		direction.Y *= -1;
		break;
	case Edge::VERTICAL_EDGE:
		direction.X *= -1;
		break;
	}

	// apply new direction
	direction.normalise ( );
	setDirection(direction);
}

const float Ball::calculatePaddleReturnAngle ( const GameObject & paddle, const Vector2Int & collisionPoint ) const
{ 
	int relativeX = collisionPoint.X - paddle.getGridX ( );

	float angleStep = (float) ( PADDLE_RETURN_ANGLE_MAX * 2) / paddle.getWidth ( );

	float returnAngle = ( angleStep * relativeX ) ;
	returnAngle += 90 - PADDLE_RETURN_ANGLE_MAX;

	return returnAngle;
}

