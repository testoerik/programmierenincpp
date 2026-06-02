#include "./GameOfLife.h"
#include <gtest/gtest.h>

TEST(GameOfLife, showState) {
  GameOfLife gameOfLife(60, 60, nullptr);
  gameOfLife.actlStPtr_[60] = true;
  gameOfLife.showState();
  ASSERT_EQ(gameOfLife.actlStPtr_[60], true);
  ASSERT_FALSE(gameOfLife.actlStPtr_[59]);
}

TEST(GameOfLife, processUserInput) {

  UserInput userInput;
  GameOfLife gameOfLife(20, 20, nullptr);
  userInput.keycode_ = 'g';
  int nCols = gameOfLife.numCols_;

  gameOfLife.processUserInput(userInput);

  ASSERT_TRUE(gameOfLife.actlStPtr_[1]);
  ASSERT_TRUE(gameOfLife.actlStPtr_[2 * (nCols) + 2]);
  ASSERT_FALSE(gameOfLife.actlStPtr_[3 * nCols]);

  gameOfLife.stateGame_ = true;
  userInput.keycode_ = 32;
  gameOfLife.processUserInput(userInput);
  ASSERT_FALSE(gameOfLife.stateGame_);
  ASSERT_TRUE(gameOfLife.processUserInput(userInput));

  userInput.keycode_ = 'q';
  ASSERT_FALSE(gameOfLife.processUserInput(userInput));

  userInput.keycode_ = 's';
  ASSERT_TRUE(gameOfLife.processUserInput(userInput));

  userInput.keycode_ = 'r';
  ASSERT_TRUE(gameOfLife.processUserInput(userInput));
}

TEST(GameOfLife, numAliveNeighbors) {
  GameOfLife gameOfLife(35, 45, nullptr);
  int nCols = gameOfLife.numCols_;
  gameOfLife.actlStPtr_[2 * nCols + 1] = true;
  gameOfLife.actlStPtr_[3 * nCols] = true;
  gameOfLife.actlStPtr_[3 * nCols + 1] = true;
  gameOfLife.actlStPtr_[3 * nCols + 2] = true;
  gameOfLife.actlStPtr_[4 * nCols + 1] = true;

  EXPECT_EQ(gameOfLife.numAliveNeighbors(3, 1), 4);
  EXPECT_EQ(gameOfLife.numAliveNeighbors(3, 0), 3);
  EXPECT_EQ(gameOfLife.numAliveNeighbors(5, 1), 1);
}
