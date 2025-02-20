#pragma once

#include "Enemy.h"
#include "Player.h"

class Guard : public Enemy
{
private:
    sf::Vector2i Movingpoints[2];
    int CurrentWaypoint;
    Player* playerRef;
public:

    Guard(float Spawnx, float Spawny, float radius, sf::Vector2f PatrolPoint1, sf::Vector2f PatrolPoint2, Grid& grid, Player& player);

    void update(float deltaTime, Grid& grid) override;

    void IdleBehavior(Grid& grid, float pathfinderdeltatime) override;

    void Showpath(sf::RenderWindow& window) override;
    sf::Vector2f GetCurrentWaypointPos() { return sf::Vector2f(Movingpoints[CurrentWaypoint].x * CELL_SIZE, Movingpoints[CurrentWaypoint].y * CELL_SIZE); }
};