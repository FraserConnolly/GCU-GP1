#pragma once
#include "Projectile.h"

enum class POWER_UP_TYPE
{
	UNSET,
	
	SPEED_INCREASE,
	SPEED_DECREASE,
	PADDLE_INCREASE,
	PADDLE_DECREASE,
	BALL_MULTIPLY,
	BALL_PENETRATE,

	NO_POWER_UP,
	NO_POWER_UP_02,
	NO_POWER_UP_03,
	NO_POWER_UP_04,
	NO_POWER_UP_05,

	POWER_UP_COUNT
};

class PowerUp :
    public Projectile
{
public:

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

	void onCollision(const GameObject& collision, const Point & collisionPoint) override
	{
		setActive(false);
	}

	/// <summary>
	/// Must be called before launch.
	/// </summary>
	/// <param name="type">The type of power up this projectile should be.</param>
	void setPowerUp( const POWER_UP_TYPE type );

	virtual void launch ( const Point startGridPosition, const float speed ) override;

	const POWER_UP_TYPE getPowerUp() const
	{
		return m_powerUpType;
	}

private:
	RenderCellData m_symbol[1];

	POWER_UP_TYPE m_powerUpType = POWER_UP_TYPE::UNSET;
};


