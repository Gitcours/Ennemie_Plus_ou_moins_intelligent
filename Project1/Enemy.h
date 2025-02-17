#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    static float SPEED;
    static float RANGE;
    Enemy(float Spawnx, float Spawny);
    void update(float deltaTime, Grid& grid) override;
};