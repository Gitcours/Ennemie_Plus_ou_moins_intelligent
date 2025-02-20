#include "Enemy.h"
#include <cmath>



Enemy::Enemy(float Spawnx, float Spawny, float radius, int hp) : Entity(Spawnx, Spawny, sf::Color::Green, hp ) {
    position = sf::Vector2f(Spawnx, Spawny);
    detectionRadius = radius;
}

void Enemy::update(float deltaTime, Grid& grid, std::vector<std::shared_ptr<Entity>> enemies) {

}

bool Enemy::detectPlayer(sf::Vector2f playerPos) {
    float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
    return (distance < detectionRadius);
}

void Enemy::Setcolor(sf::Color color) {
	shape.setFillColor(color);
}

void Enemy::SetPath(const std::vector<sf::Vector2i>& newPath) {
    path = newPath;
    currentPathIndex = 0;
}