#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float Spawnx, float Spawny, float radius) : Entity(Spawnx, Spawny, sf::Color::Green), currentPathIndex(0), detectionRadius(radius), pathfindlastpos(0, 0) {
    position = sf::Vector2f(Spawnx, Spawny);
}
bool Enemy::detectPlayer(sf::Vector2f playerPos) {
    float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
    return (distance < detectionRadius);
}

void Enemy::Setcolor(sf::Color color) {
	shape.setFillColor(color);
}

bool Enemy::Goto(sf::Vector2f target, Grid& grid, float resetpathdeltatime) {

    if (clockpathfinder.getElapsedTime() > sf::milliseconds(resetpathdeltatime) && target != pathfindlastpos) {
        clockpathfinder.restart();
        pathfindlastpos = target;
        if (!path.empty()) { path.clear(); }
    }

    if (ShapeCanPass(shape, target, grid) && path.empty())
    {
        sf::Vector2f direction = target - position;
        float distance = std::sqrt(pow(direction.x, 2) + pow(direction.y, 2));

        if (distance < 1.0f) {
            return true;
        }

        direction /= distance;
        position += direction * 2.0f;
        shape.setPosition(position);
    }

    else if (!path.empty()) {
        sf::Vector2f direction = sf::Vector2f(path[0].x * CELL_SIZE, path[0].y * CELL_SIZE) - position;
        float distance = std::sqrt(pow(direction.x, 2) + pow(direction.y, 2));

        if (distance < 1.0f) {
            path.erase(path.begin());
        }

        direction /= distance;
        position += direction * 2.0f;
        shape.setPosition(position);
    }

    else
    {
        sf::Vector2i start = sf::Vector2i(Getcenter(shape)) / CELL_SIZE;
        sf::Vector2i end = sf::Vector2i(target) / CELL_SIZE;
        path = pathfinder.findPath(grid, start, end);
    }

    return false;
}