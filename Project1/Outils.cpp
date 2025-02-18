#include "Outils.h"

int Raycast(const sf::Vector2f& Origin, const sf::Vector2f& Target, float maxdist, Grid& grid) {

    sf::Vector2f direction = Target - Origin;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= distance;

    sf::Vector2f currentPos = Origin;
    float traveledDistance = 0.0f;

    while (traveledDistance < maxdist && traveledDistance < std::sqrt(std::pow(Target.x - Origin.x, 2) + std::pow(Target.y - Origin.y, 2))) {
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
        if (traveledDistance >= std::sqrt(std::pow(Target.x - Origin.x, 2) + std::pow(Target.y - Origin.y, 2)))
        {
            return 1;
        }
    }
}

sf::Vector2f Getcenter(sf::Shape& shape) {
    return sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width / 2, shape.getPosition().y + shape.getGlobalBounds().height / 2);
}

sf::Vector2f GetTopRight(sf::Shape& shape) {
	return sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width, shape.getPosition().y);
}

sf::Vector2f GetBottomLeft(sf::Shape& shape) {
	return sf::Vector2f(shape.getPosition().x, shape.getPosition().y + shape.getGlobalBounds().height);
}

sf::Vector2f GetBottomRight(sf::Shape& shape) {
	return sf::Vector2f(shape.getPosition().x + shape.getGlobalBounds().width, shape.getPosition().y + shape.getGlobalBounds().height);
}

bool ShapeCanPass(sf::Shape& OriginShape, sf::Shape& TargetShape, float maxdist, Grid& grid) {
    if (Raycast(OriginShape.getPosition(), TargetShape.getPosition(), maxdist, grid) == 1 && Raycast(GetTopRight(OriginShape), GetTopRight(TargetShape), maxdist, grid) == 1 && Raycast(GetBottomLeft(OriginShape), GetBottomLeft(TargetShape), maxdist, grid) == 1 && Raycast(GetBottomRight(OriginShape), GetBottomRight(TargetShape), maxdist, grid) == 1)
	{
		return true;
	}
    else
    {
        return false;
    }
}