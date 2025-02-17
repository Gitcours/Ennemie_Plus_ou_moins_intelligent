#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

using namespace sf;

class Enemy : public Entity {
public:
    static float SPEED;
    static float RANGE;
    Enemy(float Spawnx, float Spawny, Vector2f startPos, float radius);
    void update(float deltaTime, Grid& grid) override;
    void patrol();
    sf::Vector2f position;
    float detectionRadius;
    void chase(sf::Vector2f playerPos);
    bool detectPlayer(sf::Vector2f playerPos);
};

#endif // ENEMY_HPP