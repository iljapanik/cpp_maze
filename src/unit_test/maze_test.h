#pragma once


#include "tests.h"


class MazeTest : public ::testing::Test {
 protected:
  std::unique_ptr<Model> model_;
  UserInput state_;



  void SetUp() override;
};
