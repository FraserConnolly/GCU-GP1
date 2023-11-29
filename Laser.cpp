#include "Laser.h"

void Laser::launch ( const COORD startGridPosition, const float speed )
{ 
	if ( m_isInFlight )
	{
		// If this happens then there is a fault.
		// An in flight projectile should never be launched again.
		return;
	}

	m_isInFlight = true;
	m_speed = speed;
	setGridPosition ( startGridPosition.X, startGridPosition.Y );
}

void Laser::tick ( GameSource * game )
{
	if ( ! m_isInFlight )
	{
		return;
	}

	translate ( 0, m_speed * game->deltaTime * 1 );

	// check for out of bounds
	if ( getGridY ( ) >= game->getScreenHeight ( ) )
	{
		m_isInFlight = false;
		
		// move the projectile off of the render grid.
		setGridPosition ( -1, -1 );
		return;
	}
}

