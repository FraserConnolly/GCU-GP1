#pragma once
#include "GameObject.h"

// forward declaration 
class ParanoidGameSource;
enum class POWER_UP_TYPE;

class Paddle : 
	public GameObject
{
public:
	Paddle() : GameObject(10, 1)
	{
		for (size_t i = 0; i < 10; i++)
		{
			m_symbol[i].UnicodeChar = 0x203E;
			m_symbol[i].Attributes = CellColour::Fore_White;
		}
	}

	// Inherited via GameObject
	const pRenderCellData draw() const override
	{
		return m_active ? (pRenderCellData)m_symbol : nullptr;
	};

	void onCollision(const GameObject& collision, const Point & collisionPoint) override
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

