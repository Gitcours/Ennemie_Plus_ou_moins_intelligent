#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include <vector>
#include <iostream>


const int WINDOW_WIDTH = 1980;
const int WINDOW_HEIGHT = 1080;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);
    std::vector<Enemy> enemies = { Enemy(100.0f, 100.0f,Vector2f(100, 100), 300.0f) };
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
            if (enemy.detectPlayer(player.shape.getPosition())) {
                enemy.shape.setFillColor(sf::Color::Red);

                enemy.chase(player.shape.getPosition());

            }
            else {
                enemy.patrol();
                enemy.shape.setFillColor(sf::Color::Green);
            }
         
        }

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (const auto& enemy : enemies)
            window.draw(enemy.shape);
        window.display();
    }
    return 0;
}

