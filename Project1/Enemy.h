#pragma once

#include "Entity.h"

class Enemy : public Entity {

protected:
    sf::Vector2f position;
    sf::Vector2f pathfindlastpos;
    float detectionRadius;
    Pathfinding pathfinder;
    std::vector<sf::Vector2i> path;
    size_t currentPathIndex;
    sf::Clock clockpathfinder;

public:

    Enemy(float Spawnx, float Spawny, float radius, int hp);

    bool detectPlayer(sf::Vector2f playerPos);

    void Setcolor(sf::Color color);

    bool ispathempty() { return path.empty(); };

    bool Goto(sf::Vector2f target, Grid& grid, float resetpathdeltatime);

    virtual void IdleBehavior(Grid& grid, float pathfinderdeltatime) = 0;

    virtual void Showpath(sf::RenderWindow& window) = 0;
};