#include "Guard.h"

Guard::Guard(float Spawnx, float Spawny, float radius, int hp, sf::Vector2f PatrolPoint1, sf::Vector2f PatrolPoint2, Grid& grid, Player& player) : Enemy(Spawnx, Spawny, radius, hp) {
    playerRef = &player;
    Movingpoints[0] = sf::Vector2i(PatrolPoint1) / CELL_SIZE;
	Movingpoints[1] = sf::Vector2i(PatrolPoint2) / CELL_SIZE;
    CurrentWaypoint = 0;
    for (auto& points : Movingpoints) {
        sf::Vector2i gridwaypoint = static_cast<sf::Vector2i>(points);
        if (!grid.getCell(gridwaypoint.x, gridwaypoint.y).walkable)
        {
            std::cerr << "Le point de patrouille en x: " << points.x << " et y: " << points.y << " est sur un mur, merci de choisir un autre point et reessayer" << std::endl;
            std::exit(EXIT_FAILURE);
        }
	}
}

void Guard::IdleBehavior(Grid& grid, float pathfinderdeltatime) {
    if (Goto(sf::Vector2f(Movingpoints[CurrentWaypoint].x * CELL_SIZE, Movingpoints[CurrentWaypoint].y * CELL_SIZE), grid, pathfinderdeltatime)) {
		CurrentWaypoint = (CurrentWaypoint + 1) % 2;
    }
}

void Guard::Showpath(sf::RenderWindow& window) {
    if (!path.empty())
    {
        for (auto& point : path) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(point.x * CELL_SIZE, point.y * CELL_SIZE);
            cell.setFillColor(sf::Color::Magenta);
            window.draw(cell);
        }
    }
}

void Guard::update(float deltaTime, Grid& grid, std::vector<std::shared_ptr<Entity>> neededEntities) {

}