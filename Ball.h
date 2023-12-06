#pragma once
#include "Projectile.h"
class Ball :
    public Projectile
{
public:
	Ball( ) : Projectile(0, 0)
	{

		m_symbol[0].UnicodeChar = 0x25CF; // Bullet 
		// 0x2022 small bullet 
		// 0x25CC hollow circle 
		// 0x20DD circle
		m_symbol[0].Attributes = CellColour::Fore_White;
	}

	// Inherited via GameObject
	const pRenderCellData draw() const override
	{
		return (pRenderCellData)m_symbol;
	}

	void onCollision(const GameObject& collision, const Point collisionPoint) override;
	void tick(GameSource* game) override;

private:
	RenderCellData m_symbol[1];
	
	// Used to know whether the object we collided with is 
	// above, below, left or right of the ball.
	Point m_previousGridPosition;
	bool m_penetrate = false;

	void applyChangeOfDirection(const Point collissionPoint);
};

