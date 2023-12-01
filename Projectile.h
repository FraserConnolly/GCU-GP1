#pragma once
#include "GameObject.h"
#include <windows.h>

class GameSource;

class Projectile :
    public GameObject
{
public:

    Projectile ( int xDirection, int yDirection )
        : GameObject ( 1, 1 ),
        m_xDirection ( xDirection ),
        m_yDirection ( yDirection ),
        m_speed ( 0 )
    {
        m_active = false;
    }

    virtual void launch ( const COORD startGridPosition, const float speed );
    virtual void tick ( GameSource * game );

protected:

    virtual bool outOfBoundsCheck ( const int width, const int height );

    float m_speed = 0;
    int m_xDirection = 0;
    int m_yDirection = 0;

};
