#pragma once

#include "Entity.h"

class Enemy : public Entity {

protected:
    sf::Vector2f position;
    float detectionRadius;
    Pathfinding pathfinder;
    std::vector<sf::Vector2i> path;
    size_t currentPathIndex;

public:
    void update(float deltaTime, Grid& grid, std::vector<std::shared_ptr<Entity>> enemies) override;

    Enemy(float Spawnx, float Spawny, float radius, int hp);

    bool detectPlayer(sf::Vector2f playerPos);

    void Setcolor(sf::Color color);

    void SetPath(const std::vector<sf::Vector2i>& path);

    bool ispathempty() { return path.empty(); };

    virtual void Goto(sf::Vector2f playerPos) = 0;

    virtual void IdleBehavior(Grid& grid) = 0;
};