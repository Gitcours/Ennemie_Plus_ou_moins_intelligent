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

    Player player(1000, 500, 10);
    sf::Vector2f playerlastposition = sf::Vector2f(-1, -1);

    std::vector<std::shared_ptr<Entity>> enemies;

    enemies.push_back(std::make_shared<Guard>(500, 500, 300, 100, sf::Vector2f(300, 500), sf::Vector2f(800, 500), grid, player));
    enemies.push_back(std::make_shared<Guard>(500, 500, 300, 100, sf::Vector2f(500, 800), sf::Vector2f(500, 200), grid, player));
    enemies.push_back(std::make_shared<Guard>(500, 500, 300, 100, sf::Vector2f(1000, 800), sf::Vector2f(200, 800), grid, player));
    enemies.push_back(std::make_shared<Guard>(500, 500, 300, 100, sf::Vector2f(800, 800), sf::Vector2f(200, 200), grid, player));

    sf::Vector2f randompos(gennbint(0, WINDOW_WIDTH), gennbint(0, WINDOW_HEIGHT));
    sf::RectangleShape celltemp(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    Pathfinding pathfinder;

    sf::Clock clock;

    while (window.isOpen()) {

        window.clear();
        grid.draw(window);
        player.Draw(window);

        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid, enemies);
        for (auto& entity : enemies) {

            std::vector<sf::Vector2i> path;

            if (typeid(*entity) == typeid(Guard))
            {
                Enemy* enemy = dynamic_cast<Enemy*>(entity.get());

                //enemy->Showpath(window, sf::Color::Cyan);

                if (enemy->detectPlayer(player.getShape().getPosition())) {
                    if (enemy->getHealth() > 30)
                    {
                        enemy->Setcolor(sf::Color::Red);
                        enemy->Goto(player.getShape().getPosition(), grid, 1000);
                        //Shaperaycastshow(enemy->getShape(), Getcenter(player.getShape()), grid, sf::Color::Magenta, window);
                        playerlastposition = Getcenter(player.getShape());
                    }
                    else
                    {
                        enemy->Setcolor(sf::Color::White);
                        while (std::sqrt(std::pow(randompos.x - playerlastposition.x, 2) + std::pow(randompos.y - playerlastposition.y, 2)) < 300 || !grid.getCell(randompos.x / CELL_SIZE, randompos.y / CELL_SIZE).walkable)
                        {
                            randompos = sf::Vector2f(gennbint(0, WINDOW_WIDTH), gennbint(0, WINDOW_HEIGHT));
                            celltemp.setPosition(randompos.x, randompos.y);
                            celltemp.setFillColor(sf::Color::Magenta);
                        }
                        enemy->Goto(randompos, grid, 1000);
                        //Shaperaycastshow(enemy->getShape(), Getcenter(player.getShape()), grid, sf::Color::Magenta, window);
                        playerlastposition = Getcenter(player.getShape());
                    }
                }
                else if (playerlastposition != sf::Vector2f(-1, -1) && enemy->getHealth() > 30) {
                    enemy->Setcolor(sf::Color::Yellow);
                    //Shaperaycastshow(enemy->getShape(), playerlastposition, grid, sf::Color::Magenta, window);
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
        }

        for (auto& enemy : enemies) {
            if (enemy->isAlive()) {
                enemy->Draw(window);
            }
        }
        //window.draw(celltemp);
        window.display();
    }
    return 0;
}