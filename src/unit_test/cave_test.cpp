#include "cave_test.h"


void CaveTest::SetUp() {
    auto errorHandler = [](ErrorType) {};  
    auto wallMapUpdated = []() {};         
    auto pathConfigured = [](std::stack<std::pair<int, int>>&) {};  
    model_ = std::make_unique<Model>(errorHandler, wallMapUpdated, pathConfigured);


    state_.type = MapType::Cave;
    state_.cols = 5;
    state_.rows = 5;
    state_.birth_limit = BirthLimit::Five;
    state_.death_limit = DeathLimit::Five;
    state_.chance = 51;
    state_.user_action = UserAction::None;
    state_.file_operation_type = FileOperationType::None;
}

TEST_F(CaveTest, Cave1) {
    state_.user_action = UserAction::Generate;
    model_->HandleUpdateState(state_);
    EXPECT_EQ(model_->GetWallMap()->m_walls_bottom.getCols(), state_.cols);
	EXPECT_EQ(model_->GetWallMap()->m_walls_bottom.getRows(), state_.rows);
}