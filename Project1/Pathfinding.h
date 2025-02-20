#pragma once

#include "Grid.h"
#include "Node.h"
#include <vector>

class Pathfinding {
public:
    static std::vector<sf::Vector2i> findPath(Grid& grid, sf::Vector2i start, sf::Vector2i end);
};