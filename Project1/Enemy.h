#pragma once

#include "Entity.h"

using namespace sf;

class Enemy : public Entity {
private :
    sf::Vector2f position;
    float detectionRadius;
    static float SPEED;
    static float RANGE;
public:
    Enemy(float Spawnx, float Spawny, float radius);
    void update(float deltaTime, Grid& grid) override;
    void patrol();
    void chase(sf::Vector2f playerPos);
    bool detectPlayer(sf::Vector2f playerPos);
};