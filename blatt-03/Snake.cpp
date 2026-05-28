#include "./Snake.h"
#include <unistd.h>

// ____________________________________________________________________________
void Snake::play() {
  terminalManager_ = new TerminalManager();
  terminalManager_->setup();
  numPixelsX_ = terminalManager_->numCols();
  numPixelsY_ = terminalManager_->numRows();
  initGame();
  drawBorder(TerminalManager::Green);
  drawSnake(TerminalManager::Red);
  terminalManager_->refresh();

  double speed = 10;

  // Acceleration in pixel per second squared.
  double acceleration = 2;

  // The absolute distance moved since the last call to moveSnake(). If it
  // becomes > 1 we have to move the snake by one pixel.
  double distance = 0;
  while (true) {
    // Let the game run until the snake has moved by at least one pixel.
    while (true) {
      UserInput userInput = terminalManager_->getUserInput();
      if (userInput.isEscape()) {
        terminalManager_->cleanup();
        return;
      }
      handleKey(userInput);
      usleep(1000);
      distance += speed / 1000;
      speed += acceleration / 1000;
      if (distance >= 1.0) {
        distance -= 1.0;
        break;
      }
    }

    // Move the snake to the next position (leave a trail of white pixels).
    drawSnake(TerminalManager::Green);
    moveSnake();
    drawSnake(TerminalManager::Red);
    terminalManager_->refresh();

    // If the snake collides with the border, quit after three seconds.
    if (collidesWithBorder()) {
      usleep(3'000'000);
      terminalManager_->cleanup();
      return;
    }
  }
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
    terminalManager_->drawPixel(0, x, color);
    terminalManager_->drawPixel(numPixelsY_ - 1, x, color);
  }

  for (int y = 0; y < numPixelsY_; y++) {
    terminalManager_->drawPixel(y, 0, color);
    terminalManager_->drawPixel(y, numPixelsX_ - 1, color);
  }
}

// ____________________________________________________________________________
void Snake::drawSnake(int color) {
  terminalManager_->drawPixel(posY_, posX_, color);
}

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
void Snake::handleKey(UserInput userInput) {
  int oldVx = dirX_;
  int oldVy = dirY_;
  if (userInput.isKeyDown()) {
    if (dirY_ != -1) {
      dirY_ = 1;
      dirX_ = 0;
    }
  } else if (userInput.isKeyUp()) {
    if (dirY_ != 1) {
      dirY_ = -1;
      dirX_ = 0;
    }
  } else if (userInput.isKeyLeft()) {
    if (dirX_ != 1) {
      dirX_ = -1;
      dirY_ = 0;
    }
  } else if (userInput.isKeyRight()) {
    if (dirX_ != -1) {
      dirX_ = 1;
      dirY_ = 0;
    }
  }
}
