#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Guard.h"
#include "Grid.h"
#include "Pathfinding.h"
#include "Outils.h"


const int WINDOW_WIDTH = 1980;
const int WINDOW_HEIGHT = 1080;


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Grid grid;
    grid.loadFromFile("map.txt");

    Player player(200, 400);

    sf::Vector2f playerlastposition = sf::Vector2f(-1, -1);

    std::vector<std::unique_ptr<Enemy>> enemies;
    enemies.push_back(std::make_unique<Guard>(500, 500, 300, sf::Vector2f(300, 500), sf::Vector2f(800, 500), grid, player));

    Pathfinding pathfinder;

    sf::Clock clock;

    while (window.isOpen()) {
        window.clear();
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid);
        for (auto& enemy : enemies) {

            std::vector<sf::Vector2i> path;

            enemy->update(deltaTime, grid);
            if (enemy->detectPlayer(player.getShape().getPosition())) {
                enemy->Setcolor(sf::Color::Red);
                enemy->Goto(player.getShape().getPosition(), grid, 1000);
                playerlastposition = Getcenter(player.getShape());
            }
            else if (playerlastposition != sf::Vector2f(-1, -1)) {
                enemy->Setcolor(sf::Color::Yellow);
                if (enemy->Goto(playerlastposition, grid, 1000))
                {
                    playerlastposition = sf::Vector2f(-1, -1);
                }
            }
            else {
                enemy->Setcolor(sf::Color::Green);
                enemy->IdleBehavior(grid, 1000);
            }
        }

        grid.draw(window);
        player.Draw(window);

        for (auto& enemy : enemies) {
            enemy->Showpath(window);
            enemy->Draw(window);
        }
        window.display();
    }
    return 0;
}