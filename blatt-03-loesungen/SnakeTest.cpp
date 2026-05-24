#include "./Snake.h"
#include <gtest/gtest.h>

TEST(Snake, initGame) {
  Snake snake;
  snake.initGame();
  ASSERT_EQ(snake.vx_, 0);
  ASSERT_EQ(snake.vx_, 1);
}
