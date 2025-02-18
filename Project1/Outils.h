#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

int Raycast(const sf::Vector2f& Origin, const sf::Vector2f& Target, float maxdist, Grid& grid, sf::RenderWindow& window); //0 = pas de collision, 1 = collision avec targetshape, 2 = collision avec mur

sf::Vector2f Getcenter(sf::Shape& shape);