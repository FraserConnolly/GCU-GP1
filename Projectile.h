#pragma once
#include "GameObject.h"

class GameSource;

class Projectile :
    public GameObject
{
public:

    Projectile ( float xDirection, float yDirection )
        : GameObject ( 1, 1 ),
        m_direction ( xDirection, yDirection ),
        m_speed ( 0 )
    {
        m_active = false;
    }

    virtual void launch ( const Vector2Int startGridPosition, const float speed );
    virtual void tick ( GameSource * game );
    virtual void onCollision ( const GameObject & collision, const Vector2Int & collisionPoint ) override
    {
        GameObject::onCollision ( collision, collisionPoint );
    }

    inline void setDirection(const Vector2 & direction)
    {
        m_direction = direction;
    }

    void setDirection(const float xDirection, const float yDirection)
    {
        m_direction.X = xDirection;
        m_direction.Y = yDirection;
    }

    Vector2 getDirection ( ) const
    {
        return m_direction;
    }

    void rotate ( const float angleInDegres )
    {
        m_direction.rotateVector ( angleInDegres );
    }

    void setSpeed(const float speed)
    {
        m_speed = speed;
    }

protected:

    virtual bool outOfBoundsCheck ( const int width, const int height );

    float m_speed = 0;
    Vector2 m_direction;

};
