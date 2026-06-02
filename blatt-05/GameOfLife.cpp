// Created by eh295
#include "GameOfLife.h"
#include <cstdlib>
#include <unistd.h>
// ___________________________________________________________________________
void GameOfLife::play() {
  while (true) {
    UserInput userInput = terminalManager_->getUserInput();
    if (processUserInput(userInput) == false) {
      break;
    }
    if (stateGame_ == true) {
      updateState();
    }
    showState();
    usleep(50'000);
  }
}

// ___________________________________________________________________________
void GameOfLife::showState() {
  if (terminalManager_ == nullptr) {
    return;
  }

  int numAliveCells = 0;
  for (int row = 0; row < terminalManager_->numRows() - 1; ++row) {
    for (int col = 0; col < numCols_; ++col) {
      bool cellVal = actlStPtr_[row * numCols_ + col];
      if (cellVal) {
        numAliveCells += 1;
        terminalManager_->drawPixel(row, col, TerminalManager::White);
      } else {
        terminalManager_->drawPixel(row, col, TerminalManager::Blue);
      }
    }
  }
  terminalManager_->refresh();
}

// ___________________________________________________________________________
GameOfLife::GameOfLife(int rows, int cols, TerminalManager *terminalManager) {
  terminalManager_ = terminalManager;
  actlStPtr_ = actualState_;
  nxtStPtr_ = nextState_;
  numRows_ = rows;
  numCols_ = cols;
  posX_ = cols / 2;
  posY_ = rows / 2;

  for (int i = 0; i < MAX_NUM_CELLS; ++i) {
    actlStPtr_[i] = false;
    nxtStPtr_[i] = false;
  }
  stateGame_ = false;
}

// ___________________________________________________________________________
bool GameOfLife::processUserInput(UserInput userInput) {
  if (userInput.isKeyMouse()) {
    int row = userInput.eventY();
    int col = userInput.eventX();
    actlStPtr_[row * numCols_ + col] = !actlStPtr_[row * numCols_ + col];
  } else if (userInput.isKeySpace()) {
    stateGame_ = !stateGame_;
  } else if (userInput.isKeyR()) {
    for (int row = 0; row < terminalManager_->numRows(); ++row) {
      for (int col = 0; col < numCols_; ++col) {
        if (rand() % 5 == 0) {
          actlStPtr_[row * numCols_ + col] = true;
        } else {
          actlStPtr_[row * numCols_ + col] = false;
        }
      }
    }
  } else if (userInput.isKeyQ()) {
    return false;
  } else if (userInput.isKeyS()) {
    updateState();
  } else if (userInput.isKeyG()) {
    actlStPtr_[1] = true;
    actlStPtr_[numCols_ + 2] = true;
    actlStPtr_[2 * numCols_] = true;
    actlStPtr_[2 * numCols_ + 1] = true;
    actlStPtr_[2 * numCols_ + 2] = true;
  }
  return true;
}

// ___________________________________________________________________________
int GameOfLife::numAliveNeighbors(int row, int col) {
  int aliveCount = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int nRow = row + i;
      int nCol = col + j;
      if (i == 0 && j == 0) {
        continue;
      }
      if ((nRow >= 0 && nRow < terminalManager_->numRows()) &&
          (nCol >= 0 && nCol < numCols_)) {
        if (actlStPtr_[nRow * numCols_ + nCol]) {
          aliveCount += 1;
        }
        continue;
      }
    }
  }
  return aliveCount;
}

// ___________________________________________________________________________
void GameOfLife::updateState() {
  for (int row = 0; row < terminalManager_->numRows(); ++row) {
    for (int col = 0; col < numCols_; ++col) {
      int neighbors_ = numAliveNeighbors(row, col);
      if (actlStPtr_[row * numCols_ + col] &&
          (neighbors_ == 2 || neighbors_ == 3)) {
        nxtStPtr_[row * numCols_ + col] = true;
      } else if (actlStPtr_[row * numCols_ + col] == false && neighbors_ == 3) {
        nxtStPtr_[row * numCols_ + col] = true;
      } else {
        nxtStPtr_[row * numCols_ + col] = false;
      }
    }
  }
  bool *tmp = actlStPtr_;
  actlStPtr_ = nxtStPtr_;
  nxtStPtr_ = tmp;
}
