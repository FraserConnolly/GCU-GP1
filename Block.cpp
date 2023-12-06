#include "Block.h"

void Block::onCollision(const GameObject& collision, const Point collisionPoint)
{
	m_damage++;

	char16_t c;

	switch (m_damage)
	{
	case 0:
		c = BlockChar::FULL;
		break;
	case 1:
		c = BlockChar::DAMAGED_1;
		break;
	case 2:
		c = BlockChar::DAMAGED_2;
		break;
	case 3:
	default:
		c = BlockChar::DESTROYED;
		setActive(false);
		break;
	}

	for (size_t i = 0; i < m_width; i++)
	{
		m_symbol[i].UnicodeChar = c;
	}
}
