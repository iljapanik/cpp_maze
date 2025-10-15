#pragma once

#include "IGenerationStrategy.h"
#include "GenerationConfigCave.h"
#include <memory>

class CaveGenerationStrategy : public IGenerationStrategy
{
  public:
    using IGenerationStrategy::IGenerationStrategy;

    void GenerateMap(const IGenerationConfig &config,
                     const std::shared_ptr<WallMap> &wall_map) override;

  private:
    void generateCave(const GenerationConfigCave &config,
                      const std::shared_ptr<WallMap> &wall_map);
};
