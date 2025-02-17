#include "Outils.h"

// Fonction de raycasting
int performRaycasting(const sf::Shape& baseshape, const sf::Shape& targetshape, float maxdist, Grid& grid) {
    sf::Vector2f baseCenter = sf::Vector2f(
        baseshape.getPosition().x + baseshape.getGlobalBounds().width / 2,
        baseshape.getPosition().y + baseshape.getGlobalBounds().height / 2
    );

    sf::Vector2f targetCenter = sf::Vector2f(
        targetshape.getPosition().x + targetshape.getGlobalBounds().width / 2,
        targetshape.getPosition().y + targetshape.getGlobalBounds().height / 2
    );

    sf::Vector2f direction = targetCenter - baseCenter;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= distance;

    sf::Vector2f currentPos = baseCenter;
    float traveledDistance = 0.0f;

    while (traveledDistance < maxdist && traveledDistance < std::sqrt(std::pow(targetCenter.x - baseCenter.x, 2) + std::pow(targetCenter.y - baseCenter.y, 2))) {
        int gridX = static_cast<int>(currentPos.x / CELL_SIZE);
        int gridY = static_cast<int>(currentPos.y / CELL_SIZE);

        if (gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) {
            break;
        }
        if (!grid.getCell(gridX, gridY).walkable) {
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
