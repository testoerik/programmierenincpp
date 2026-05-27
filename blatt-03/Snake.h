#pragma once
#include "./TerminalManager.h"
#include <gtest/gtest_prod.h>
class Snake {
private:
  // The total number of logical pixels on the screen.
  int numPixelsX_;
  int numPixelsY_;

  // The position of the snake in pixels.
  int posX_;
  int posY_;

  // The directions X and Y of our snake.
  int dirX_;
  int dirY_;

  TerminalManager *terminalManager_;
  FRIEND_TEST(SnakeTest, initGame);
  FRIEND_TEST(SnakeTest, moveSnake);
  FRIEND_TEST(SnakeTest, handleKey);
  FRIEND_TEST(SnakeTest, collidesWithBorder);

public:
  // Play a game of snake.
  void play();

  // ___________________________________________________________________________
  // Initialize the terminal for use with ncurses commands.
  void initTerminal();

  // Initialize the game.
  void initGame();
  // Draw the snake (show == true: draws in black, show == true: draws in
  // white).
  void drawSnake(int color);

  // Draw a border around the screen.
  void drawBorder(int color);

  // Return true iff the head of the snake is on our out of the border
  bool collidesWithBorder();

  // Update the position of the  snake when `milliseconds` have passed since the
  // last call to `moveSnake`
  void moveSnake();

  // Update the direction and the speed of the snake given the last pressed key.
  void handleKey(UserInput userInput);
};
