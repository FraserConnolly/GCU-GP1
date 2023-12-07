#pragma once
#include "GameObject.h"

class Block : 
	public GameObject
{
public:

	Block() : GameObject(8, 1)
	{
		setActive(false);
		for (size_t i = 0; i < m_width * m_height; i++)
		{
			m_symbol[i].UnicodeChar = 0x2588;
			m_symbol[i].Attributes = CellColour::Fore_White;
		}
	}

	// Inherited via GameObject
	const pRenderCellData draw() const override
	{
		return (pRenderCellData)m_symbol;
	};

	enum BlockChar : char16_t
	{
		FULL      = 0x2588,
		DAMAGED_1 = 0x2592,
		DAMAGED_2 = 0x2591,
		DESTROYED = 0x0000
	};

	void onCollision(const GameObject& collision, const Point collisionPoint);

	void setColour(CellColour colour)
	{
		for (size_t i = 0; i < m_width * m_height; i++)
		{
			m_symbol[i].Attributes = colour;
		}
	}

private:
	RenderCellData m_symbol[8];

	int m_damage = 0;
};

