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
		switch ( m_powerUpType )
		{
			case POWER_UP_TYPE::PADDLE_SPEED_INCREASE:
				m_symbol [ 0 ].UnicodeChar = '>';
				m_symbol [ 0 ].Attributes = CellColour::Fore_White | CellColour::Back_Green;
				break;
			case POWER_UP_TYPE::PADDLE_SPEED_DECREASE:
				m_symbol [ 0 ].UnicodeChar = '<';
				m_symbol [ 0 ].Attributes = CellColour::Fore_White | CellColour::Back_Red;
				break;
			case POWER_UP_TYPE::PADDLE_INCREASE:
				m_symbol [ 0 ].UnicodeChar = '+';
				m_symbol [ 0 ].Attributes = CellColour::Fore_White | CellColour::Back_Green;
				break;
			case POWER_UP_TYPE::PADDLE_DECREASE:
				m_symbol [ 0 ].UnicodeChar = '-';
				m_symbol [ 0 ].Attributes = CellColour::Fore_White | CellColour::Back_Red;
				break;
			case POWER_UP_TYPE::BALL_MULTIPLY:
				m_symbol [ 0 ].UnicodeChar = '*';
				m_symbol [ 0 ].Attributes = CellColour::Fore_White | CellColour::Back_Green;
				break;
			case POWER_UP_TYPE::BALL_PENETRATE:
				m_symbol [ 0 ].UnicodeChar = '!';
				m_symbol [ 0 ].Attributes = CellColour::Fore_White | CellColour::Back_Green;
				break;
			default:
				m_symbol [ 0 ].UnicodeChar = '?';
				m_symbol [ 0 ].Attributes = CellColour::Fore_White;
				break;
		}

		Projectile::launch ( startGridPosition, speed );
	}
}
