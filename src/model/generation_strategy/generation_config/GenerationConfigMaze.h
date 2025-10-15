#include "IGenerationConfig.h"

// заглушка для MazeGenerationStrategy, так как там не требуется доп конфигурация
class GenerationConfigMaze : public IGenerationConfig
{
  public:
	GenerationConfigMaze() = default;
	GenerationConfigMaze(int rows, int cols) : IGenerationConfig(rows, cols) {}
};