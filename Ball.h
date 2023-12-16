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
class Paddle;
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

	void onCollision(const GameObject& collision, const Vector2Int& collisionPoint) override;
	void tick(GameSource* game) override;
	
	void applyPowerUp ( const POWER_UP_TYPE type, ParanoidGameSource * const game );
	void resetPowerUps ( );

private:
	RenderCellData m_symbol[1];
	
	// Used to know whether the object we collided with is 
	// above, below, left or right of the ball.
	Vector2Int m_previousGridPosition;
	bool m_penetrate = false;
	bool m_powerUpApplied = false;
	float m_powerUpResetTime = 0;

	void applyChangeOfDirection ( const Edge edge );
	
	/// <summary>
	/// Gets the angle at which the ball should return at having hit the paddle.
	/// Direction must be set to Left ( -1, 0 ) before applying the result of this function.
	/// Note that grid positions are used rather than the absolute position of the ball and the paddle.
	/// This reduced complexity but it also gives the player a fairer experience as they can't know the absolute position of 
	/// either the paddle or the ball.
	/// </summary>
	/// <param name="paddle">The paddle that this ball has collided with.</param>
	/// <param name="collisionPoint">The grid position that the ball hit the paddle.</param>
	/// <returns>
	/// Angle in degrees. 
	/// 90 represents straight up.
	/// </returns>
	const float calculatePaddleReturnAngle( const GameObject & paddle, const Vector2Int & collisionPoint ) const;
};

