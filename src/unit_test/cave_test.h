#pragma once


#include <gtest/gtest.h>
#include <unistd.h>

#include "Model.h"


class CaveTest : public ::testing::Test {
 protected:
  std::unique_ptr<Model> model_;
  UserInput state_;



  void SetUp() override;
};
