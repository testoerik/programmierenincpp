// Copyright 2024, University of Freiburg
// Chair of Algorithms and Data Structures
// Author: Hannah Bast <bast@cs.uni-freiburg.de>,
//         Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>

#include "./Snake.h"
#include <ncurses.h>
#include <unistd.h>

// ___________________________________________________________________________
void Snake::play() {
  initTerminal();
  initGame();
  drawBorder(COLOR_BLUE);
  drawSnake(COLOR_GREEN);
  refresh();
  // Initial speed in pixels per second.
  double speed = 10;

  // Acceleration in pixel per second squared.
  double acceleration = 2;

  // The absolute distance moved since the last call to moveSnake(). If it
  // becomes > 1 we have to move the snake by one pixel.
  double distance = 0;
  while (true) {
    while (true) {
      if (!handleKey(getch())) {
        endwin();
        return;
      }
      usleep(1000);
      distance += speed / 1000;
      speed += acceleration / 1000;
      if (distance >= 1.0) {
        distance -= 1.0;
        break;
      }
    }
    drawSnake(COLOR_BLACK);
    moveSnake();
    drawSnake(COLOR_GREEN);
    refresh();
    if (collidesWithBorder()) {
      // Game over, wait for the escape key to be pressed.
      while (handleKey(getch())) {
      }
      endwin();
      return;
    }
  }
}

// ____________________________________________________________________________
void Snake::initTerminal() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);

  start_color();
  // Initialize one color pair for each color.
  // For simplicity reasons we only use the foreground
  // colors.
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);

  // COLS and LINES are global variables from ncurses (dimensions of screen).
  numPixelsX_ = COLS / 2;
  numPixelsY_ = LINES;
}

// ____________________________________________________________________________
void Snake::initGame() {
  posX_ = numPixelsX_ / 2;
  posY_ = numPixelsY_ / 2;

  vx_ = 1;
  vy_ = 0;
}

// _____________________________________________________________________________
void Snake::drawPixel(int y, int x, int color) {
  int colorPairNum = 1;
  if (color == COLOR_RED) {
    colorPairNum = 2;
  } else if (color == COLOR_BLACK) {
    colorPairNum = 3;
  } else if (color == COLOR_BLUE) {
    colorPairNum = 4;
  }
  attron(COLOR_PAIR(colorPairNum));
  for (int j = 0; j < 2; j++) {
    mvprintw(y, x * 2 + j, " ");
  }
}

// ____________________________________________________________________________
void Snake::drawBorder(int color) {
  for (int x = 0; x < numPixelsX_; x++) {
    drawPixel(0, x, color);
    drawPixel(numPixelsY_ - 1, x, color);
  }

  for (int y = 0; y < numPixelsY_; y++) {
    drawPixel(y, 0, color);
    drawPixel(y, numPixelsX_ - 1, color);
  }
}

// ____________________________________________________________________________
void Snake::drawSnake(int color) { drawPixel(posY_, posX_, color); }

// ____________________________________________________________________________
bool Snake::collidesWithBorder() {
  int x = posX_;
  int y = posY_;
  return x <= 0 || x >= numPixelsX_ - 1 || y <= 0 || y >= numPixelsY_ - 1;
}

// ____________________________________________________________________________
void Snake::moveSnake() {
  posX_ = posX_ + vx_;
  posY_ = posY_ + vy_;
}

// ____________________________________________________________________________
bool Snake::handleKey(int key) {
  int oldVx = vx_;
  int oldVy = vy_;
  switch (key) {
  case 27: // ESC
    return false;
  case KEY_DOWN:
    vx_ = 0;
    vy_ = 1;
    break;
  case KEY_UP:
    vx_ = 0;
    vy_ = -1;
    break;
  case KEY_LEFT:
    vx_ = -1;
    vy_ = 0;
    break;
  case KEY_RIGHT:
    vx_ = 1;
    vy_ = 0;
    break;
  default:
    break;
  }
  // Ignore the change of direction if it is illegal
  if (oldVx + vx_ == 0 && oldVy + vy_ == 0) {
    vx_ = oldVx;
    vy_ = oldVy;
  }

  return true;
}
