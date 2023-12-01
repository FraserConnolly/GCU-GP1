#pragma once
#include "GameObject.h"
#include <windows.h>

class GameSource;

class Projectile :
    public GameObject
{
public:
    
    Projectile( int xDirection, int yDirection ) 
        : GameObject(1, 1),
        m_xDirection(xDirection), m_yDirection(yDirection)
    {

    }

    virtual void launch(const COORD startGridPosition, const float speed);
    virtual void tick(GameSource* game);

    const bool getInFlight() const
    {
        return m_isInFlight;
    }

protected:

    virtual bool outOfBoundsCheck( const int width, const int height );

    float m_speed = 0;
    int m_xDirection = 0;
    int m_yDirection = 0;
    bool m_isInFlight = false;
};

