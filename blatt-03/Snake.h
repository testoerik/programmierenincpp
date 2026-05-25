#pragma once
#include "TerminalManager.h"

class Snake {

private:
  // The current position of our snake.
  int posRow_;
  int posCol_;

  // The current direction of our snake.
  int dirRow_;
  int dirCol_;
  // The TerminalManager for rendering our game.
  TerminalManager *terminalManager_;

public:
  void play();

private:
  void initGame();

  void drawBorder(int color);

  void drawSnake(int color);

  bool collidesWithBorder();

  void moveSnake();

  bool handleKey(int key);
};
