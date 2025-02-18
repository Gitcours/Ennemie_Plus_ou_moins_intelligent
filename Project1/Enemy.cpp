#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float Spawnx, float Spawny, float radius) : Entity(Spawnx, Spawny, sf::Color::Green ) {
    position = sf::Vector2f(Spawnx, Spawny);
    detectionRadius = radius;
}

bool Enemy::detectPlayer(sf::Vector2f playerPos) {
    float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
    return (distance < detectionRadius);
}

void Enemy::Setcolor(sf::Color color) {
	shape.setFillColor(color);
}