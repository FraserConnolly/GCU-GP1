#pragma once
#include "GameObject.h"

#define BLOCK_MAX_CELL_COUNT 50

class Block : 
	public GameObject
{
public:

	Block();
	
	Block(const int width, const int height);

	// Inherited via GameObject
	const pRenderCellData draw() const override
	{
		return (pRenderCellData)m_symbol;
	};

	void onCollision( const GameObject& collision, const Point & collisionPoint );
	void setColour( const CellColour colour );
	void setDamage( const int damage );
	const bool isCorner( const Point& point ) const;

private:
	RenderCellData m_symbol[BLOCK_MAX_CELL_COUNT];

	int m_damage = 0;
};

