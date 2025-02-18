#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Outils.h"
#include "Pathfinding.h"

class Entity {
protected:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

public:

    Entity(float x, float y, sf::Color color);

    void Draw(sf::RenderWindow& window);
    virtual void update(float deltaTime, Grid& grid) = 0;

    sf::Shape& getShape() { return shape; }
};