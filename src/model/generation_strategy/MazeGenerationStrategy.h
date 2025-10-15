#pragma once
#include "GenerationConfigMaze.h"
#include "IGenerationStrategy.h"
#include <memory>

class MazeGenerationStrategy : public IGenerationStrategy
{
public:
    using IGenerationStrategy::IGenerationStrategy;

    void GenerateMap(const IGenerationConfig &config,
                     const std::shared_ptr<WallMap> &wall_map) override;

private:
    void GenerateMazeLogic(const GenerationConfigMaze &config,
                           const std::shared_ptr<WallMap> &wall_map);
};
