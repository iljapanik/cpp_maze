#include "maze_test.h"

void MazeTest::SetUp()
{

	auto errorHandler = [](ErrorType) {};
	auto wallMapUpdated = []() {};
	auto pathConfigured = [](std::stack<std::pair<int, int>> &) {};
	model_ = std::make_unique<Model>(errorHandler, wallMapUpdated, pathConfigured);

	state_.type = MapType::Maze;
	state_.cols = 5;
	state_.rows = 5;
	state_.user_action = UserAction::Generate;
	state_.file_operation_type = FileOperationType::None;


}

TEST_F(MazeTest, Maze1)
{
	model_->HandleUpdateState(state_);
	EXPECT_EQ(model_->GetWallMap()->m_walls_bottom.getCols(), state_.cols);
	EXPECT_EQ(model_->GetWallMap()->m_walls_bottom.getRows(), state_.rows);
}

TEST_F(MazeTest, Maze2)
{
	state_.cols = 0;
	state_.rows = 0;
	model_->HandleUpdateState(state_);
}

TEST_F(MazeTest, Maze3){
	state_.pointA_x = 0;
	state_.pointA_y = 0;

	state_.pointB_x = 3;
	state_.pointB_y = 3;

	state_.user_action = UserAction::Generate;
	model_->HandleUpdateState(state_);

	state_.user_action = UserAction::FindPath;

	

	model_->HandleUpdateState(state_);

	EXPECT_EQ(model_->GetWallMap()->m_walls_bottom.getRows(), state_.rows); 
	EXPECT_EQ(model_->GetWallMap()->m_walls_bottom.getCols(), state_.cols);
}