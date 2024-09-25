#include "map.hpp"

#include <gtest/gtest.h>

TEST(MapTest, CheckDefaultValues)
{
  map::GridMap grid_map;
  EXPECT_EQ(grid_map.get_width(), 50u);
  EXPECT_EQ(grid_map.get_height(), 50u);
}

TEST(MapTest, CheckValues)
{
  map::GridMap grid_map(70, 70);
  EXPECT_EQ(grid_map.get_width(), 70u);
  EXPECT_EQ(grid_map.get_height(), 70u);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
