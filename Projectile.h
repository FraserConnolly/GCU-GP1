#pragma once
#include "GameObject.h"

class GameSource;

class Projectile :
    public GameObject
{
public:

    Projectile ( int xDirection, int yDirection )
        : GameObject ( 1, 1 ),
        m_xDirection ( (float) xDirection ),
        m_yDirection ( (float) yDirection ),
        m_speed ( 0 )
    {
        m_active = false;
    }

    virtual void launch ( const Point startGridPosition, const float speed );
    virtual void tick ( GameSource * game );
    virtual void onCollision ( const GameObject & collision, const Point & collisionPoint ) override
    {
        GameObject::onCollision ( collision, collisionPoint );
    }

    inline void setDirection(const FPoint & direction)
    {
        setDirection(direction.X, direction.Y);
    }

    void setDirection(const float xDirection, const float yDirection)
    {
        m_xDirection = xDirection;
        m_yDirection = yDirection;
    }

    void setSpeed(const float speed)
    {
        m_speed = speed;
    }

protected:

    virtual bool outOfBoundsCheck ( const int width, const int height );

    float m_speed = 0;
    float m_xDirection = 0;
    float m_yDirection = 0;

};
