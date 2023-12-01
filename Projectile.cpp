#include "Projectile.h"
#include "GameSource.h"

void Projectile::launch(const COORD startGridPosition, const float speed)
{
	if (m_isInFlight)
	{
		// If this happens then there is a fault.
		// An in flight projectile should never be launched again.
		return;
	}

	m_isInFlight = true;
	m_speed = speed;
	setGridPosition(startGridPosition.X, startGridPosition.Y);
}

void Projectile::tick(GameSource* game)
{
	if (!m_isInFlight)
	{
		return;
	}

	translate(m_speed * game->deltaTime * m_xDirection, m_speed * game->deltaTime * m_yDirection );

	if (outOfBoundsCheck(game->getScreenWidth(), game->getScreenHeight()))
	{
		m_isInFlight = false;

		// move the projectile off of the render grid.
		setGridPosition(-1, -1);
	}

}

bool Projectile::outOfBoundsCheck( const int width, const int height )
{
	if (getGridY() < 0)
	{
		return true;
	}
	
	if (getGridY() >= height)
	{
		return true;
	}

	if (getGridX() < 0)
	{
		return true;
	}

	if (getGridX() >= width)
	{
		return true;
	}

	return false;
}