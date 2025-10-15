#include "CaveGenerationStrategy.h"
#include <random>
#include <stdexcept>

void CaveGenerationStrategy::GenerateMap(const IGenerationConfig &config,
                                         const std::shared_ptr<WallMap> &wall_map)
{
    auto caveConfig = dynamic_cast<const GenerationConfigCave *>(&config);
    if (!caveConfig)
        throw std::runtime_error("Invalid config type for CaveGenerationStrategy");

    if (BaseCheck(*caveConfig)){
        generateCave(*caveConfig, wall_map);
    }
}

void CaveGenerationStrategy::generateCave(const GenerationConfigCave &config,
                                          const std::shared_ptr<WallMap> &wall_map)
{
    int rows_ = config.get_rows();
    int cols_ = config.get_cols();
    int chance = config.get_chance();

    wall_map->m_walls_right.resize(rows_, cols_);
    wall_map->m_walls_bottom.resize(rows_, cols_);
    wall_map->Clear();

    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<int> dist(1, 100);

    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            if (dist(gen) > (100 - chance))
            {
                wall_map->m_walls_bottom(i, j) = 1;
                wall_map->m_walls_right(i, j) = 1;
            }
            else
            {
                wall_map->m_walls_bottom(i, j) = 0;
                wall_map->m_walls_right(i, j) = 0;
            }
        }
    }
}
