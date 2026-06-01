#include "./GameOfLife.h"
#include <gtest/gtest.h>

TEST(GameOfLife, showState) {
  GameOfLife gameOfLife;
  gameOfLife.actlStPtr_[60] = true;
  showState() ASSERT_EQ(gameOfLife.actlStPtr_[60], TerminalManager::White);
}
