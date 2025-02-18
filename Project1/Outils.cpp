#include "Outils.h"

int Raycast(const sf::Vector2f& Origin, const sf::Vector2f& Target, float maxdist, Grid& grid) {
    sf::Vector2f baseCenter = sf::Vector2f(
        Origin.x,
        Origin.y
    );

    sf::Vector2f targetCenter = sf::Vector2f(
        Target.x,
        Target.y
    );

    sf::Vector2f direction = targetCenter - baseCenter;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= distance;

    sf::Vector2f currentPos = baseCenter;
    float traveledDistance = 0.0f;

    while (traveledDistance < maxdist && traveledDistance < std::sqrt(std::pow(targetCenter.x - baseCenter.x, 2) + std::pow(targetCenter.y - baseCenter.y, 2))) {
        int gridX = static_cast<int>(currentPos.x / CELL_SIZE);
        int gridY = static_cast<int>(currentPos.y / CELL_SIZE);

        if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT || !grid.getCell(gridX, gridY).walkable) {
            return 2;
        }

        currentPos += direction;
        traveledDistance += 1.0f;
        if (traveledDistance >= maxdist)
        {
            return 0;
        }
        if (traveledDistance >= std::sqrt(std::pow(targetCenter.x - baseCenter.x, 2) + std::pow(targetCenter.y - baseCenter.y, 2)))
        {
            return 1;
        }
    }
}

sf::Vector2f Getcenter(sf::Shape& shape) {
    return sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width / 2, shape.getPosition().y + shape.getGlobalBounds().height / 2);
}