#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float Spawnx, float Spawny , Vector2f startPos, float radius) : Entity(Spawnx, Spawny, sf::Color::Green ) {
    position = startPos;
    detectionRadius = radius;
}

void Enemy::patrol() {
    static int currentWaypoint = 0;
    static sf::Vector2f waypoints[2] = { sf::Vector2f(100, 300), sf::Vector2f(500, 300) };
    sf::Vector2f target = waypoints[currentWaypoint];
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.0f) {
        currentWaypoint = (currentWaypoint + 1) % 2;
    }
    else {
        direction /= distance;
        position += direction * 2.0f;
    }
    shape.setPosition(position);
}

bool Enemy::detectPlayer(sf::Vector2f playerPos) {
    float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
    return (distance < detectionRadius);
}

void Enemy::chase(sf::Vector2f playerPos) {
    sf::Vector2f direction = playerPos - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        
        direction /= distance;
        position += direction * 2.0f;
    }
    shape.setPosition(position);
}

void Enemy::update(float deltaTime, Grid& grid) {

}
