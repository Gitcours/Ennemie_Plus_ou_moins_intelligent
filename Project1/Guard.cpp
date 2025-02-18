#include "Guard.h"

Guard::Guard(float Spawnx, float Spawny, float radius) : Enemy(Spawnx, Spawny, radius) {}

void Guard::IdleBehavior() {
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

void Guard::PlayerDetectedBehavior(sf::Vector2f playerPos) {
    sf::Vector2f direction = playerPos - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 0) {

        direction /= distance;
        position += direction * 2.0f;
    }
    shape.setPosition(position);
}

void Guard::update(float deltaTime, Grid& grid) {

}