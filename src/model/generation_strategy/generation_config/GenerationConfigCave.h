#include "IGenerationConfig.h"

// брать эту конфигурацию для алгоритма клеточного автомата
class GenerationConfigCave : public IGenerationConfig
{
  public:
	GenerationConfigCave() = default;
	GenerationConfigCave(int rows, int cols) : IGenerationConfig(rows, cols) {}
	GenerationConfigCave(int rows, int cols, int chance) : IGenerationConfig(rows, cols)
	{
		chance_ = chance;
	}

	int get_chance() const { return chance_; }

  private:

	int chance_;
};