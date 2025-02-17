#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

int performRaycasting(const sf::Shape& baseshape, const sf::Shape& targetshape, float maxdist, Grid& grid); //0 = pas de collision, 1 = collision avec targetshape, 2 = collision avec mur