#include "Block.h"



enum BlockChar : char16_t
{
#ifndef USE_BLOCK_DEBUG_VISUAL
	FULL = 0x2588,
	DAMAGED_1 = 0x2592,
	DAMAGED_2 = 0x2591,
	DESTROYED = 0x0000
#else
	FULL = '3',
	DAMAGED_1 = '2',
	DAMAGED_2 = '1',
	DESTROYED = ' '
#endif
};

Block::Block() : GameObject(8, 2)
{
	setActive(false);
	setDamage(0);
	setColour(CellColour::Fore_White);
}

Block::Block(const int width, const int height) : GameObject(width, height)
{
	if (width * height > BLOCK_MAX_CELL_COUNT)
	{
		// this block is too large to fit in the underlying data structure.
		throw;
	}

	setActive(false);

	setDamage(0);
	setColour(CellColour::Fore_White);
}

void Block::onCollision(const GameObject& collision, const Vector2Int & collisionPoint)
{
	setDamage(m_damage + 1);
}


void Block::setColour(const CellColour colour)
{
	for (size_t i = 0; i < m_width * m_height; i++)
	{
		m_symbol[i].Attributes = colour;
	}
}

void Block::setDamage(const int damage)
{
	m_damage = damage;

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

	for (size_t i = 0; i < m_width * m_height; i++)
	{
		m_symbol[i].UnicodeChar = c;
	}
}

/// <summary>
/// Checks if the specified point is one of the four corners of this block.
/// </summary>
/// <param name="point">Point to check.</param>
/// <returns>True if the specified point is the same point as a corner of this block.</returns>
const bool Block::isCorner(const Vector2Int& point) const
{
	if (point == getGridPosition())
	{
		return true;
	}

	if (point.X == getGridX() && point.Y == getGridY() + (getHeight() - 1))
	{
		return true;
	}

	if (point.X == getGridX() + ( getWidth( ) - 1) && point.Y == getGridY( ))
	{
		return true;
	}
	
	if (point.X == getGridX() + (getWidth() - 1) && point.Y == getGridY() + (getHeight() - 1))
	{
		return true;
	}

	return false;
}
