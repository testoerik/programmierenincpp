#include "Snake.h"
#include <unistd.h>
#include "./TerminalManager.h"
void Snake::play() {
  initTerminal();
  initGame();
  double speed = 8.0;
  double acceleration = 1.5;

  clear();
  drawBorder(1);
  drawSnake(2);
  refresh();

  while (true) {
    int sleep_time_us = 1'000'000 / speed;
    usleep(sleep_time_us);
    int key = getch();
    if (key != ERR) {
      if (handleKey(key)) {
        break;
      }
    }
    moveSnake();
    if (collidesWithBorder()) {
      break;
    }
    clear();
    drawBorder(1);
    drawSnake(2);
    refresh();

    speed += acceleration * (sleep_time_us / 1'000'000.0);
  }
  mvprintw(LINES / 2, (COLS / 2) - 5, "GAME OVER!");
  mvprintw((LINES / 2) + 1, (COLS / 2) - 10, "Press ESC to exit...");
  refresh();

  while (true) {
    if (getch() == 27) {
      break;
    }
    usleep(1000);
  }
  endwin();
}

// ___________________________________________________________________________
void Snake::initGame() {
  posRow_ = LINES / 2;
  posCol_ = COLS / 2;
  dirCol_ = KEY_RIGHT;
}

// ___________________________________________________________________________
void Snake::drawBorder(int color) {
  for (int i = 0; i < posRow_; ++i) {
   drawPixel(0, i, color);
   drawPixel(posCol_ - 1, i, color);
  }

  for (int j = 0; j < posCol_; ++j) {
   drawPixel(j, 0, color);
   drawPixel(j, posRow_ - 2, color);
  }
}

// ___________________________________________________________________________
void Snake::drawSnake(int color) {drawPixel(posCol_ / 2, posRow_ / 2, color); }
// ___________________________________________________________________________
bool Snake::collidesWithBorder() {
	return }

// ___________________________________________________________________________
void Snake::moveSnake() {
  switch (dirPxl_) {
  case KEY_UP:
    posCol_ -= 1;
    break;
  case KEY_DOWN:
    posCol_ += 1;
    break;
  case KEY_RIGHT:
    posRow_ += 1;
    break;
  case KEY_LEFT:
    posRow_ -= 1;
    break;
  }
}

// ___________________________________________________________________________
bool Snake::handleKey(int key) {
  if (key == 27) {
    return true;
  } else if (key == KEY_UP && dirPxl_ != KEY_DOWN) {
    dirPxl_ = KEY_UP;
  } else if (key == KEY_DOWN && dirPxl_ != KEY_UP) {
    dirPxl_ = KEY_DOWN;
  } else if (key == KEY_LEFT && dirPxl_ != KEY_RIGHT) {
    dirPxl_ = KEY_LEFT;
  } else if (key == KEY_RIGHT && dirPxl_ != KEY_LEFT) {
    dirPxl_ = KEY_RIGHT;
  }
  return false;
}
