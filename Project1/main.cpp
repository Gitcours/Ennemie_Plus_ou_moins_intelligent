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
    std::vector<Enemy> enemies = { Enemy(500, 500, 300) };
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
                if (Raycast(Getcenter(enemy.shape), Getcenter(player.shape), 300, grid) == 1) {
                    enemy.chase(player.shape.getPosition());
                }
                else if (Raycast(Getcenter(enemy.shape), Getcenter(player.shape), 300, grid) == 2) {
                    enemy.shape.setFillColor(sf::Color::Green);
                    enemy.patrol();
                }
               

            }
            else {
                enemy.patrol();
                enemy.shape.setFillColor(sf::Color::Green);
            }
        }
        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        
        for (auto& enemy : enemies) {
            std::cout << Raycast(Getcenter(enemy.shape), Getcenter(player.shape), 300, grid) << std::endl;
            window.draw(enemy.shape);
        }
        window.display();
    }
    return 0;
}