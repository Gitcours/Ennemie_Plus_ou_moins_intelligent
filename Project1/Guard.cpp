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

void Guard::IdleBehavior(Grid& grid) {
    if (ShapeCanPass(shape, sf::Vector2f(Movingpoints[CurrentWaypoint].x * CELL_SIZE, Movingpoints[CurrentWaypoint].y * CELL_SIZE), grid))
    {
        if (!path.empty()) { path.clear(); }

        sf::Vector2f direction = sf::Vector2f(Movingpoints[CurrentWaypoint].x * CELL_SIZE, Movingpoints[CurrentWaypoint].y * CELL_SIZE) - position;
        float distance = std::sqrt(pow(direction.x, 2) + pow(direction.y, 2));

        if (distance < 1.0f) {
            CurrentWaypoint = (CurrentWaypoint + 1) % 2;
        }

        direction /= distance;
        position += direction * 2.0f;
        shape.setPosition(position);
    }
    else
    {
        if (path.empty())
        {
            sf::Vector2i start = sf::Vector2i(Getcenter(shape)) / CELL_SIZE;
            sf::Vector2i end = sf::Vector2i(Getcenter(playerRef->getShape())) / CELL_SIZE;
            path = pathfinder.findPath(grid, start, end);
        }
        if (!path.empty()) {
            //std::cout << "Path to player found!" << std::endl;
            sf::Vector2f direction = sf::Vector2f(path[0].x * CELL_SIZE, path[0].y * CELL_SIZE) - position;
            float distance = std::sqrt(pow(direction.x, 2) + pow(direction.y, 2));

            if (distance < 1.0f) {
				path.erase(path.begin());
            }

            direction /= distance;
            position += direction * 2.0f;
            shape.setPosition(position);
        }
        else {
            //std::cout << "No path to player found." << std::endl;
        }
    }
}

void Guard::Goto(sf::Vector2f target) {
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance > 0) {

        direction /= distance;
        position += direction * 2.0f;
    }
    shape.setPosition(position);
}

void Guard::update(float deltaTime, Grid& grid, std::vector<std::shared_ptr<Entity>> enemies) {
    if (!path.empty() && currentPathIndex < path.size()) {
        sf::Vector2f targetPosition(path[currentPathIndex].x * 40.0f, path[currentPathIndex].y * 40.0f);
        sf::Vector2f direction = targetPosition - shape.getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < 1.0f) {
            currentPathIndex++;
        }
        else {
            direction /= distance;
            shape.move(direction * 100.0f * deltaTime); // Vitesse de l'ennemi
        }
    }
}