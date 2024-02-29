#include "example.hpp"

#include <gtest/gtest.h>

TEST(ReadTest, CheckValues)
{
  const auto d = MatioEigenExample::read_first("./data/data.mat", "dd");
  ASSERT_GE(d, 0.8);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
