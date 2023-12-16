#pragma once
#include "GameObject.h"

#define PADDLE_WIDTH_NORMAL 10
#define PADDLE_WIDTH_SMALL   4
#define PADDLE_WIDTH_LARGE  25

#define PADDLE_CHAR 0x203E
#define PADDLE_COLOUR CellColour::Fore_White

#define PADDLE_SPEED 40
#define PADDLE_SPEED_POWER_UP_MULTIPLYER 0.2

#define POWER_UP_DURATION 5.0

// forward declaration 
class ParanoidGameSource;
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

	void tick( ParanoidGameSource * const game);

	void applyPowerUp(const POWER_UP_TYPE type, ParanoidGameSource * const game );

	void resetPowerUps();

private:
	RenderCellData m_symbol[ PADDLE_WIDTH_LARGE ];

	float m_speed = PADDLE_SPEED;
	bool m_powerUpApplied = false;
	float m_powerUpResetTime = 0;

	void processMovement(ParanoidGameSource * const game);
	void processInput(ParanoidGameSource * const game);
	void resizePaddle ( unsigned int newSize );
};

