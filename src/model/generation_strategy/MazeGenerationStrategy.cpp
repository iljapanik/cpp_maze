#include "MazeGenerationStrategy.h"
#include <stdexcept>

void MazeGenerationStrategy::GenerateMap(const IGenerationConfig &config,
                                         const std::shared_ptr<WallMap> &wall_map)
{
    auto mazeConfig = dynamic_cast<const GenerationConfigMaze *>(&config);
    if (!mazeConfig)
        throw std::runtime_error("Invalid config type for MazeGenerationStrategy");

    if (BaseCheck(*mazeConfig)){
        GenerateMazeLogic(*mazeConfig, wall_map);
    }
}

void MazeGenerationStrategy::GenerateMazeLogic(const GenerationConfigMaze &config,
                                               const std::shared_ptr<WallMap> &wall_map)
{
    auto gen_rand = randomFunc_(0, 1);

    int rows = config.get_rows();
    int cols = config.get_cols();
    int counter = 1;

    wall_map->m_walls_right.resize(rows, cols);
    wall_map->m_walls_bottom.resize(rows, cols);
    wall_map->m_digits_matrix.resize(rows, cols);
    wall_map->Clear();

    // первая строка
    for (int j = 0; j < cols; j++)
    {
        wall_map->m_digits_matrix(0, j) = counter;
        counter++;
    }

    for (int i = 0; i < rows; i++)
    {
        // right стены
        for (int j = 0; j < cols - 1; j++)
        {
            int value = randomFunc_(0, 1);
            if (value == 1)
            {
                wall_map->m_walls_right(i, j) = 1;
            }
            else
            {
                if (wall_map->m_digits_matrix(i, j) == wall_map->m_digits_matrix(i, j + 1))
                {
                    wall_map->m_walls_right(i, j) = 1;
                }
                else
                {
                    int from = wall_map->m_digits_matrix(i, j);
                    int to = wall_map->m_digits_matrix(i, j + 1);
                    for (int k = 0; k < cols; k++)
                    {
                        if (wall_map->m_digits_matrix(i, k) == to)
                        {
                            wall_map->m_digits_matrix(i, k) = from;
                        }
                    }
                }
            }
        }

        // bottom стены
        for (int j = 0; j < cols; j++)
        {
            int value = randomFunc_(0, 1);
            if (value == 1)
            {
                int dig = wall_map->m_digits_matrix(i, j);
                int cnt = 0;
                for (int k = 0; k < cols; k++)
                {
                    if (wall_map->m_digits_matrix(i, k) == dig &&
                        wall_map->m_walls_bottom(i, k) == 0)
                    {
                        cnt++;
                    }
                    if (cnt > 1)
                    {
                        wall_map->m_walls_bottom(i, j) = 1;
                        break;
                    }
                }
            }
        }

        // перенос строки
        if (i != rows - 1)
        {
            for (int j = 0; j < cols; j++)
            {
                wall_map->m_digits_matrix(i + 1, j) = wall_map->m_digits_matrix(i, j);
                if (wall_map->m_walls_bottom(i, j) == 1)
                    wall_map->m_digits_matrix(i + 1, j) = 0;
            }

            for (int j = 0; j < cols; j++)
            {
                if (wall_map->m_digits_matrix(i + 1, j) == 0)
                {
                    wall_map->m_digits_matrix(i + 1, j) = counter;
                    counter++;
                }
            }
        }
    }

    // последняя строка
    for (int j = 0; j < cols - 1; j++)
    {
        if (wall_map->m_digits_matrix(rows - 1, j) != wall_map->m_digits_matrix(rows - 1, j + 1))
        {
            wall_map->m_walls_right(rows - 1, j) = 0;
        }
        wall_map->m_digits_matrix(rows - 1, j) = wall_map->m_digits_matrix(rows - 1, j + 1);
        wall_map->m_walls_bottom(rows - 1, j) = 1;
    }
    wall_map->m_walls_bottom(rows - 1, cols - 1) = 1;

    // правая стенка
    for (int i = 0; i < rows; i++)
    {
        wall_map->m_walls_right(i, cols - 1) = 1;
    }
}
