#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
public:
    static float SPEED;
    static float RANGE;
    Enemy(float Spawnx, float Spawny);
    void update(float deltaTime, Grid& grid) override;
};

#endif // ENEMY_HPP