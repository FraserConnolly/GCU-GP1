#include "PowerUp.h"


/// <summary>
/// Must be called before launch.
/// </summary>
/// <param name="type">The type of power up this projectile should be.</param>

void PowerUp::setPowerUp ( const POWER_UP_TYPE type )
{
	if ( m_active )
	{
		// can not change power up type on an active power up.
		return;
	}

	if ( type == POWER_UP_TYPE::UNSET || type >= POWER_UP_TYPE::NO_POWER_UP )
	{
		m_powerUpType = POWER_UP_TYPE::UNSET;
		return;
	}

	m_powerUpType = type;
}

void PowerUp::launch ( const Point startGridPosition, const float speed )
{
	// Only launch if the power up has been set.
	if ( m_powerUpType > POWER_UP_TYPE::UNSET && m_powerUpType < POWER_UP_TYPE::NO_POWER_UP )
	{
		Projectile::launch ( startGridPosition, speed );
	}
}
