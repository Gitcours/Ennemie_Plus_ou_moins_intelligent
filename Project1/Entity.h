#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Outils.h"
#include "Pathfinding.h"

class Entity {
protected:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    int health;

public:

    Entity(float x, float y, sf::Color color, int hp);

    void Draw(sf::RenderWindow& window);

    virtual void update(float deltaTime, Grid& grid, std::vector<std::shared_ptr<Entity>> neededEntities) = 0;

    bool isAlive() const;

    void takeDamage(int damage);

    sf::Shape& getShape() { return shape; }

    int& getHealth() { return health; }
};