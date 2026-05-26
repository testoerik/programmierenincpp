#include "./Snake.h"
#include <ncurses.h>

// ____________________________________________________________________________
void Snake::play() {
  }

// ____________________________________________________________________________
void Snake::initGame() {
  posX_ = numPixelsX_ / 2;
  posY_ = numPixelsY_ / 2;

  dirX_ = 1;
  dirY_ = 0;
}

// ____________________________________________________________________________
void Snake::drawBorder(int color) {
  for (int x = 0; x < numPixelsX_; x++) {
    terminalManager_.drawPixel(0, x, color);
    terminalManager_.drawPixel(numPixelsY_ - 1, x, color);
  }

  for (int y = 0; y < numPixelsY_; y++) {
    terminalManager_.drawPixel(y, 0, color);
    terminalManager_.drawPixel(y, numPixelsX_ - 1, color);
  }
}

// ____________________________________________________________________________
void Snake::drawSnake(int color) {terminalManager_.drawPixel(posY_, posX_, color); }

// ____________________________________________________________________________
bool Snake::collidesWithBorder() {
  int x = posX_;
  int y = posY_;
  return x <= 0 || x >= numPixelsX_ - 1 || y <= 0 || y >= numPixelsY_ - 1;
}

// ____________________________________________________________________________
void Snake::moveSnake() {
  posX_ = posX_ + dirX_;
  posY_ = posY_ + dirY_;
}

// ____________________________________________________________________________
bool Snake::handleKey(int key) {
  int oldVx = dirX_;
  int oldVy = dirY_;
  switch (key) {
  case 27: // ESC
    return true;
  case KEY_DOWN:
    dirX_ = 0;
    dirY_ = 1;
    break;
  case KEY_UP:
    dirX_ = 0;
    dirY_ = -1;
    break;
  case KEY_LEFT:
    dirX_ = -1;
    dirY_ = 0;
    break;
  case KEY_RIGHT:
    dirX_ = 1;
    dirY_ = 0;
    break;
  default:
    break;
  }
  // Ignore the change of direction if it is illegal
  if (oldVx + dirX_ == 0 && oldVy + dirY_ == 0) {
    dirX_ = oldVx;
    dirY_ = oldVy;
  }

  return false;
}
