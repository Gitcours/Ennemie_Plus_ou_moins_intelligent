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

    Player player(200, 400, 10);
    sf::Vector2f playerlastposition;

    std::vector<std::shared_ptr<Entity>> enemies;

    enemies.push_back(std::make_unique<Guard>(500, 500, 300, 100, sf::Vector2f(300, 500), sf::Vector2f(800, 500), grid, player));

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

        player.update(deltaTime, grid, enemies);
        for (auto& enemy : enemies) {
            std::vector<sf::Vector2i> path;
            enemy->update(deltaTime, grid,enemies);
            if (typeid(*enemy) == typeid(Enemy))
            {
                Enemy* enemy2 = dynamic_cast<Enemy*>(enemy.get());
                if (enemy2->detectPlayer(player.getShape().getPosition())) {
                    enemy2->Setcolor(sf::Color::Red);
                    if (ShapeCanPass(enemy->getShape(), Getcenter(player.getShape()), grid) == true) {
                        enemy2->Goto(player.getShape().getPosition());
                        playerlastposition = Getcenter(player.getShape());
                    }
                    else
                    {
                        std::cout << "no path to player, need to set pathfinding here" << std::endl;
                    }
                }
                else if (playerlastposition != sf::Vector2f(-1, -1)) {
                    enemy2->Setcolor(sf::Color::Yellow);
                    if (std::abs(Getcenter(enemy->getShape()).x - playerlastposition.x) < 1 && std::abs(Getcenter(enemy->getShape()).y - playerlastposition.y) < 1)
                    {
                        std::cout << "Player last position reached." << std::endl;
                        playerlastposition = sf::Vector2f(-1, -1);
                    }
                    else
                    {
                        if (ShapeCanPass(enemy->getShape(), playerlastposition, grid) == true)
                        {
                            enemy2->Goto(sf::Vector2f(playerlastposition.x - player.getShape().getGlobalBounds().width / 2, playerlastposition.y - player.getShape().getGlobalBounds().height / 2));
                        }
                        else
                        {
                            std::cout << "no path to last player pos, need to set pathfinding here" << std::endl;
                            playerlastposition = sf::Vector2f(-1, -1);
                        }
                    }
                }
                else {
                    enemy2->Setcolor(sf::Color::Green);
                    enemy2->IdleBehavior(grid);
                }
            }
        }

        grid.draw(window);
        player.Draw(window);

        for (auto& enemy : enemies) {
            if(enemy->isAlive())
                enemy->Draw(window);
        }
        window.display();
    }
    return 0;
}