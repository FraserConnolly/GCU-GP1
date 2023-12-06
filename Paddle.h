#pragma once
#include "GameObject.h"

enum POWER_UP_TYPE;

// forward declaration 
class ParanoidGameSource;

class Paddle : 
	public GameObject
{
public:
	Paddle() : GameObject(10, 1)
	{
		m_symbol[0].UnicodeChar = 0x0305; // 0x033F - double line 
		m_symbol[0].Attributes = CellColour::Fore_White;
	}

	// Inherited via GameObject
	const pRenderCellData draw() const override
	{
		return m_active ? (pRenderCellData)m_symbol : nullptr;
	};

	void onCollision(const GameObject& collision, const Point collisionPoint) override
	{
		// apply bonus
	}

	void tick(ParanoidGameSource* game);

	void applyPowerUp(const POWER_UP_TYPE type);

	void resetPowerUps();

private:
	RenderCellData m_symbol[10];

	// float fireTimeout = ;
	// float m_lastFireTime = 0;

	void processMovement(ParanoidGameSource* game);
	void processInput(ParanoidGameSource* game);


};

