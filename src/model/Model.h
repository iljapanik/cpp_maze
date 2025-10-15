#pragma once
#include "CaveGenerationStrategy.h"
#include "ErrorHandler.h"
#include "FileWorker.h"
#include "MazeGenerationStrategy.h"
#include "PathFinder.h"
#include "WallMap.h"
#include "common.h"
#include <functional>
class Model
{
  public:
	using ErrorHandlerFunc = std::function<void(ErrorType)>;
	using WallMapUpdatedFunc = std::function<void(void)>;
	using StackPathConfiguredFunc = std::function<void(std::stack<std::pair<int, int>>&)>;


	Model(ErrorHandlerFunc, WallMapUpdatedFunc, StackPathConfiguredFunc);
	std::shared_ptr<WallMap> GetWallMap() const;

  private:
	void HandleGenerate(UserInput user_input);
	void HandleFindPath(UserInput user_input);
	UserInput HandleUserBadInput(UserInput user_input);
	void GenerateMap(IGenerationConfig conf);
	void CreateConfig(UserInput state);
	void CreateStrategy(UserInput state);

	void HandleUpdateCave(UserInput state);
	void updateCave(DeathLimit death, BirthLimit birth, Matrix &matrix);

	std::shared_ptr<WallMap> wall_map;
	std::unique_ptr<IGenerationStrategy> generation_strategy;
	std::unique_ptr<IGenerationConfig> generation_config;
	std::unique_ptr<PathFinder> path_finder;
	std::unique_ptr<FileWorker> file_worker;

	ErrorHandlerFunc errorFunc_;
	WallMapUpdatedFunc wallmap_updatedFunc_;
	StackPathConfiguredFunc stackpath_configuredFunc;

  public:
	// slots
	void HandleUpdateState(UserInput);
	void HandleFileOperation(UserInput);
	// signals
	void WallMapUpdated();
	void ErrorHandled(const std::string &);
	void StackPathConfigured(std::stack<std::pair<int, int>> &);
};
