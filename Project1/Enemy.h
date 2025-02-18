#pragma once

#include "Entity.h"

class Enemy : public Entity {

protected:
    sf::Vector2f position;
    float detectionRadius;

public:
    Enemy(float Spawnx, float Spawny, float radius);

    bool detectPlayer(sf::Vector2f playerPos);

    void Setcolor(sf::Color color);

    virtual void PlayerDetectedBehavior(sf::Vector2f playerPos) = 0;

    virtual void IdleBehavior() = 0;
};