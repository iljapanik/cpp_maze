#include "PathFinder.h"
#include <stdexcept>

PathFinder::PathFinder(RandomFunc random_func)
    : randomFunc_(random_func)
{
}

std::stack<std::pair<int, int>> PathFinder::FindPath(
    int x1, int y1, int x2, int y2,
    const std::shared_ptr<WallMap> &wall_map)
{
    if (wall_map)
    {
        visited_cells.resize(wall_map->m_walls_right.getRows(),
                             wall_map->m_walls_right.getCols());
        visited_cells.clear();

        stack_path.push({x1, y1});
        visited_cells(y1, x1) = 1;

        while (true)
        {
            auto [x, y] = GetRandomNeighbour(stack_path.top(), wall_map);

            if (x == x2 && y == y2)
            {
                stack_path.push({x, y});
                break;
            }

            if (x == -1 && y == -1)
            {
                stack_path.pop();
            }
            else
            {
                stack_path.push({x, y});
                visited_cells(y, x) = 1;
            }
        }
    }

    return std::move(stack_path);
}

std::pair<int, int> PathFinder::GetRandomNeighbour(
    const std::pair<int, int> &xy,
    const std::shared_ptr<WallMap> &wall_map)
{
    Directions directions;
    WallPresence walls_around;

    int x = xy.first;
    int y = xy.second;

    // Проверка выхода за границы по X
    if (x == 0)
    {
        directions.right = true;
    }
    else if (x == visited_cells.getCols() - 1)
    {
        directions.left = true;
    }
    else
    {
        directions.right = true;
        directions.left = true;
    }

    // Проверка выхода за границы по Y
    if (y == 0)
    {
        directions.down = true;
    }
    else if (y == visited_cells.getRows() - 1)
    {
        directions.up = true;
    }
    else
    {
        directions.up = true;
        directions.down = true;
    }

    // Проверка стен и посещённых клеток
    walls_around.up = !(directions.up &&
                        (wall_map->m_walls_bottom(y - 1, x) == 0) &&
                        visited_cells(y - 1, x) == 0);

    walls_around.down = !(directions.down &&
                          (wall_map->m_walls_bottom(y, x) == 0) &&
                          visited_cells(y + 1, x) == 0);

    walls_around.left = !(directions.left &&
                          (wall_map->m_walls_right(y, x - 1) == 0) &&
                          visited_cells(y, x - 1) == 0);

    walls_around.right = !(directions.right &&
                           (wall_map->m_walls_right(y, x) == 0) &&
                           visited_cells(y, x + 1) == 0);

    std::vector<Direction> available_directions;

    if (directions.up && !walls_around.up)
        available_directions.push_back(Direction::UP);
    if (directions.down && !walls_around.down)
        available_directions.push_back(Direction::DOWN);
    if (directions.left && !walls_around.left)
        available_directions.push_back(Direction::LEFT);
    if (directions.right && !walls_around.right)
        available_directions.push_back(Direction::RIGHT);

    if (available_directions.empty())
    {
        return {-1, -1};
    }

    int random_index = randomFunc_(0, static_cast<int>(available_directions.size()) - 1);

    switch (available_directions[random_index])
    {
    case Direction::UP:
        return {x, y - 1};
    case Direction::DOWN:
        return {x, y + 1};
    case Direction::LEFT:
        return {x - 1, y};
    case Direction::RIGHT:
        return {x + 1, y};
    default:
        throw std::runtime_error("Invalid direction");
    }
}
