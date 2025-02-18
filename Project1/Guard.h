#pragma once

#include "Enemy.h"

class Guard : public Enemy
{
public:

    Guard(float Spawnx, float Spawny, float radius);

    void update(float deltaTime, Grid& grid) override;

    void IdleBehavior() override;

    void PlayerDetectedBehavior(sf::Vector2f playerPos) override;
};