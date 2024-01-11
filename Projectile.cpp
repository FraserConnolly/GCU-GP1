#include "Projectile.h"
#include "GameScene.h"

void Projectile::launch ( const Vector2Int startGridPosition, const float speed )
{
	if ( m_active )
	{
		// If this happens then there is a fault.
		// An in flight projectile should never be launched again.
		return;
	}

	m_active = true;
	m_speed = speed;
	setGridPosition ( startGridPosition.X, startGridPosition.Y );
}

void Projectile::tick ( GameScene * game )
{
	if ( !m_active )
	{
		return;
	}

	translate ( m_direction * m_speed * game->getDeltaTime() );

	if ( outOfBoundsCheck ( game->getScreenWidth ( ), game->getScreenHeight ( ) ) )
	{
		m_active = false;

		// move the projectile off of the render grid.
		setGridPosition ( -1, -1 );
	}

}

bool Projectile::outOfBoundsCheck ( const int width, const int height )
{
	if ( getGridY ( ) < 0 )
	{
		return true;
	}

	if ( getGridY ( ) >= height )
	{
		return true;
	}

	if ( getGridX ( ) < 0 )
	{
		return true;
	}

	if ( getGridX ( ) >= width )
	{
		return true;
	}

	return false;
}
