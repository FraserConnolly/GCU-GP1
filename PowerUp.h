#pragma once
#include "Projectile.h"

class PowerUp :
    public Projectile
{
public:

	enum POWER_UP_TYPE
	{
		UNSET,
		SPEED_INCREASE,
		SPEED_DECREASE,
		PADDLE_INCREASE,
		PADDLE_DECREASE,
		BALL_MULTIPLY,
		BALL_PENETRATE,
	};

	PowerUp() : Projectile(0, 1)
	{
		m_symbol[0].UnicodeChar = '?';
		m_symbol[0].Attributes = CellColour::Fore_White;
	}

	// Inherited via GameObject
	const pRenderCellData draw() const override
	{
		return (pRenderCellData)m_symbol;
	}

	void onCollision(const GameObject& collision, const Point collisionPoint) override
	{
		setActive(false);
	}

	/// <summary>
	/// Must be called before launch.
	/// </summary>
	/// <param name="type">The type of power up this projectile should be.</param>
	void setPowerUp( const PowerUp::POWER_UP_TYPE type )
	{
		if (m_active)
		{
			// can not change power up type on an active power up.
			return;
		}

		m_powerUpType = type;
	}

private:
	RenderCellData m_symbol[1];

	POWER_UP_TYPE m_powerUpType = POWER_UP_TYPE::UNSET;
};


