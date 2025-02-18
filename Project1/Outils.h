#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

int Raycast(const sf::Vector2f& Origin, const sf::Vector2f& Target, Grid& grid); //0 = erreur, 1 = collision avec targetshape, 2 = collision avec mur

sf::Vector2f Getcenter(sf::Shape& shape);

sf::Vector2f GetTopRight(sf::Shape& shape);

sf::Vector2f GetBottomLeft(sf::Shape& shape);

sf::Vector2f GetBottomRight(sf::Shape& shape);

bool ShapeCanPass(sf::Shape& OriginShape, const sf::Vector2f& Target, Grid& grid);