#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Grid.h"
#include "Outils.h"
#include <vector>
#include <iostream>


const int WINDOW_WIDTH = 1980;
const int WINDOW_HEIGHT = 1080;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);
    std::vector<Enemy> enemies = { Enemy(500, 500) };
    Grid grid;
    grid.loadFromFile("map.txt");

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid);
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid);
        }

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (auto& enemy : enemies) {
            window.draw(enemy.shape);
        }
        window.display();
    }
    return 0;
}