#pragma once
#include "Projectile.h"

enum Edge
{
	RETURN,				// used to send the ball back in the direction it came.
	CORNER,				// used when the ball hits the corner of something.
	HORIZONTAL_EDGE,
	VERTICAL_EDGE		
};

#define POWER_UP_PENETRATION_DURATION 10.0

#define BALL_SYMBOL_NORMAL    0x25CF // Bullet 
#define BALL_SYMBOL_PENETRATE 0x25CC // hollow circle

class ParanoidGameSource;
enum class POWER_UP_TYPE;

class Ball :
    public Projectile
{
public:
	Ball( ) : Projectile(0, 0)
	{

		m_symbol[0].UnicodeChar = BALL_SYMBOL_NORMAL; 
		m_symbol[0].Attributes = CellColour::Fore_White;
	}

	// Inherited via GameObject
	const pRenderCellData draw() const override
	{
		return (pRenderCellData)m_symbol;
	}

	void onCollision(const GameObject& collision, const Point& collisionPoint) override;
	void tick(GameSource* game) override;
	
	void applyPowerUp ( const POWER_UP_TYPE type, ParanoidGameSource * const game );
	void resetPowerUps ( );

private:
	RenderCellData m_symbol[1];
	
	// Used to know whether the object we collided with is 
	// above, below, left or right of the ball.
	Point m_previousGridPosition;
	bool m_penetrate = false;
	bool m_powerUpApplied = false;
	float m_powerUpResetTime = 0;

	void applyChangeOfDirection(const Edge edge);
};

