#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

const int GRID_WIDTH = 49;
const int GRID_HEIGHT = 27;
const int CELL_SIZE = 40;

struct Cell {
    bool walkable;
    sf::Vector2f position;
    sf::RectangleShape shape;
};

class Grid {
public:
    Grid();
    void loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
    std::vector<std::vector<Cell>> cells;
    Cell& getCell(int x, int y);
};  
