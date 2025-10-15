#include "Model.h"
#include "Randomizer.h"


Model::Model(ErrorHandlerFunc error_func, WallMapUpdatedFunc wallmap_updated_func, StackPathConfiguredFunc stackpath_configured_func)
: errorFunc_(error_func), wallmap_updatedFunc_(wallmap_updated_func),  stackpath_configuredFunc(stackpath_configured_func)
{
	wall_map = std::make_shared<WallMap>(50, 50);
	file_worker = std::make_unique<FileWorker>();
	path_finder = std::make_unique<PathFinder>(Randomizer::universal_random);
	
}

std::shared_ptr<WallMap> Model::GetWallMap() const
{
	return wall_map;
}

void Model::HandleGenerate(UserInput state)
{
	CreateConfig(state);
	CreateStrategy(state);
	generation_strategy->GenerateMap(*generation_config, wall_map);
	wallmap_updatedFunc_();
}

void Model::HandleUpdateCave(UserInput state)
{
	if (state.type == MapType::Cave)
	{
		if (generation_strategy ||	(state.type == MapType::Cave && dynamic_cast<CaveGenerationStrategy *>(generation_strategy.get())))
		{
			updateCave(state.death_limit, state.birth_limit, wall_map->m_walls_right);
			wall_map->m_walls_bottom = wall_map->m_walls_right;
			wallmap_updatedFunc_();
		}
	}

}

void Model::HandleFindPath(UserInput state)
{
	std::stack path_stack = path_finder->FindPath(state.pointA_x, state.pointA_y, state.pointB_x, state.pointB_y, wall_map);
	stackpath_configuredFunc(path_stack);

}

UserInput Model::HandleUserBadInput(UserInput state)
{
	return state; // TODO
}

void Model::HandleUpdateState(UserInput user_input)
{
	UserInput correct_input = HandleUserBadInput(user_input);
	if (correct_input.user_action == UserAction::Generate)
	{
		HandleGenerate(correct_input);
	}
	else if (correct_input.user_action == UserAction::FindPath)
	{
		HandleFindPath(correct_input);
	}
	else if (correct_input.user_action == UserAction::FileOperation)
	{
		HandleFileOperation(correct_input);
	} 
	else if (correct_input.user_action == UserAction::Update)
	{
		HandleUpdateCave(correct_input);
	}
}

void Model::HandleFileOperation(UserInput user_input)
{
	bool rows_cols_updated = user_input.rows != wall_map->m_walls_right.getRows() || user_input.cols != wall_map->m_walls_right.getCols();

	if (user_input.type == MapType::Maze)
	{
		if (user_input.file_operation_type == FileOperationType::Import)
		{
			bool res = file_worker->ParseMap(user_input.filename, wall_map->m_walls_right, wall_map->m_walls_bottom);
			wallmap_updatedFunc_();
		}
		else if (user_input.file_operation_type == FileOperationType::Export)
		{
			file_worker->SaveMapToFile(user_input.filename, wall_map->m_walls_right, wall_map->m_walls_bottom);
		}
	}
	else if (user_input.type == MapType::Cave)
	{
		if (user_input.file_operation_type == FileOperationType::Import)
		{
			bool res = file_worker->ParseMap(user_input.filename, wall_map->m_walls_right);
			wall_map->m_walls_bottom = wall_map->m_walls_right;
			wallmap_updatedFunc_();
		}
		else if (user_input.file_operation_type == FileOperationType::Export)
		{
			file_worker->SaveMapToFile(user_input.filename, wall_map->m_walls_right);
		}
	}
}

// void Model::GenerateMap(std::uniqueIGenerationConfig config)
// {
// }

void Model::CreateConfig(UserInput state)
{
	generation_config.reset();
	switch (state.type)
	{
	case MapType::Maze:
		generation_config = std::make_unique<GenerationConfigMaze>(state.rows, state.cols);
		break;
	case MapType::Cave:
		if (state.file_operation_type == FileOperationType::Import)
		{
			generation_config = std::make_unique<GenerationConfigCave>(state.rows, state.cols);
		}
		else
		{
			generation_config = std::make_unique<GenerationConfigCave>(state.rows, state.cols, state.chance);
		}
		break;
	default:
		throw std::runtime_error("Unknown map type");
	}
}

void Model::CreateStrategy(UserInput state)
{
	if (!generation_strategy ||
		(state.type == MapType::Maze && !dynamic_cast<MazeGenerationStrategy *>(generation_strategy.get())) ||
		(state.type == MapType::Cave && !dynamic_cast<CaveGenerationStrategy *>(generation_strategy.get())))
	{
		if (state.type == MapType::Maze)
			generation_strategy = std::make_unique<MazeGenerationStrategy>(errorFunc_, Randomizer::universal_random);
		else if (state.type == MapType::Cave)
			generation_strategy = std::make_unique<CaveGenerationStrategy>(errorFunc_, Randomizer::universal_random);
		else
			throw std::runtime_error("Unknown map type");
	}
}

int countLiveSurround(Matrix cave, int rowPos, int colPos)
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int cave_i = rowPos + i;
			int cave_j = colPos + j;
			if (i == 0 && j == 0)
			{
				;
			}
			else if (cave_i < 0 || cave_j < 0 || cave_i >= cave.getRows() || cave_j >= cave.getCols())
			{
				count++;
			}
			else
			{
				count = count + cave(cave_i, cave_j);
			}
		}
	}
	return count;
}

void Model::updateCave(DeathLimit death, BirthLimit birth, Matrix &matrix)
{
	Matrix prevCave(matrix);

	for (int i = 0; i < matrix.getRows(); i++)
	{
		for (int j = 0; j < matrix.getCols(); j++)
		{
			int neighbors = countLiveSurround(prevCave, i, j);
			if (matrix(i, j) == 1 && neighbors < (int)death)
			{
				matrix(i, j) = 0;
			}
			else if (matrix(i, j) == 0 && neighbors > (int)birth)
			{
				matrix(i, j) = 1;
			}
		}
	}
}