#pragma once
#include "WallMap.h"
#include "memory"
#include <functional>
#include <stack>
struct Directions
{
	bool up{0};
	bool down{0};
	bool left{0};
	bool right{0};
};

struct WallPresence
{
	bool up{true};
	bool down{true};
	bool left{true};
	bool right{true};
};

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class PathFinder
{
  public:
	using RandomFunc = std::function<int(int min, int max)>;

	PathFinder(RandomFunc random_func);
	std::stack<std::pair<int, int>> FindPath(int x1, int y1, int x2, int y2, const std::shared_ptr<WallMap> &wall_map);

  private:
	Matrix visited_cells;
	std::stack<std::pair<int, int>> stack_path;
	RandomFunc randomFunc_;

	std::pair<int, int> GetRandomNeighbour(const std::pair<int, int> &xy, const std::shared_ptr<WallMap> &wall_map);
};