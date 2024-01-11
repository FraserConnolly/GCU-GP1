#pragma once
#include "GameObject.h"

#define PADDLE_WIDTH_NORMAL 10
#define PADDLE_WIDTH_SMALL   4
#define PADDLE_WIDTH_LARGE  25

#define PADDLE_CHAR 0x203E
#define PADDLE_COLOUR CellColour::Fore_White

#define PADDLE_SPEED 40
#define PADDLE_SPEED_POWER_UP_MULTIPLYER 0.2f

#define POWER_UP_DURATION 5.0f

// forward declaration 
class ParanoidGameMainScene;
enum class POWER_UP_TYPE;

class Paddle : 
	public GameObject
{
public:
	Paddle() : GameObject( PADDLE_WIDTH_LARGE, 1)
	{
		for (size_t i = 0; i < PADDLE_WIDTH_LARGE; i++)
		{
			m_symbol[i].UnicodeChar = PADDLE_CHAR;
			m_symbol[i].Attributes = PADDLE_COLOUR;
		}
	}

	// Inherited via GameObject
	const pRenderCellData draw() const override
	{
		return m_active ? (pRenderCellData)m_symbol : nullptr;
	};

	void tick( ParanoidGameMainScene * const game);

	void applyPowerUp(const POWER_UP_TYPE type, ParanoidGameMainScene * const game );

	void resetPowerUps();

private:
	RenderCellData m_symbol[ PADDLE_WIDTH_LARGE ];

	float m_speed = PADDLE_SPEED;
	bool m_powerUpApplied = false;
	float m_powerUpResetTime = 0;

	void processMovement(ParanoidGameMainScene * const game);
	void processInput(ParanoidGameMainScene * const game);
	void resizePaddle ( unsigned int newSize );
};

