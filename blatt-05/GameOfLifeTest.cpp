#include "./GameOfLife.h"
#include <gtest/gtest.h>
#include <ncurses.h>

TEST(GameOfLifeTest, initGame) {
  numRows = 100;
  numCols = 100;

  initGame();
  ASSERT_EQ(posX, 50);
  ASSERT_EQ(posY, 50);
  ASSERT_EQ(a[534], false);
  ASSERT_EQ(a[9999], false);
}

TEST(GameOfLifeTest, processUserInput) {
  initGame();
  processUserInput(' ');
  ASSERT_TRUE(stateGame);
  a[numCols + 2] = true;
  a[numCols + 3] = true;
  a[numCols + 4] = true;
  processUserInput('s');
  ASSERT_TRUE(a[3]);
  ASSERT_TRUE(a[numCols + 3]);
  ASSERT_TRUE(a[2 * numCols + 3]);
}

TEST(GameOfLifeTest, numAliveNeighbors) {
  initGame();
  a[numCols + 1] = true;
  a[2 * numCols + 2] = true;
  a[3 * numCols + 3] = true;
  ASSERT_EQ(numAliveNeighbors(1, 1), 1);
  ASSERT_EQ(numAliveNeighbors(2, 2), 2);
  ASSERT_EQ(numAliveNeighbors(3, 3), 1);
  ASSERT_EQ(numAliveNeighbors(1, 3), 1);
}

TEST(GameOfLifeTest, updateState) {
  initGame();
  a[numCols + 1] = true;
  a[numCols + 2] = true;
  a[numCols + 3] = true;
  updateState();
  ASSERT_TRUE(a[2]);
  ASSERT_TRUE(a[numCols + 2]);
  ASSERT_TRUE(a[2 * numCols + 2]);
  ASSERT_FALSE(a[numCols + 1]);
  ASSERT_FALSE(a[numCols + 3]);
}
