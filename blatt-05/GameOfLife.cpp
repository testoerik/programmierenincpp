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
  int numAliveCells = 0;
  for (int row = 0; row < terminalManager_->numRows() - 1; ++row) {
    for (int col = 0; col < terminalManager_->numCols(); ++col) {
      bool cellVal = actlStPtr_[row * terminalManager_->numCols() + col];
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
GameOfLife::GameOfLife(TerminalManager *terminalManager) {
  terminalManager_ = terminalManager;

  actlStPtr_ = actualState_;
  nxtStPtr_ = nextState_;
  int cols_ = terminalManager_->numCols();
  int rows_ = terminalManager_->numRows();
  posX_ = cols_ / 2;
  posY_ = rows_ / 2;

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
    actlStPtr_[row * terminalManager_->numCols() + col] =
        !actlStPtr_[row * terminalManager_->numCols() + col];
  } else if (userInput.isKeySpace()) {
    stateGame_ = !stateGame_;
  } else if (userInput.isKeyR()) {
    for (int row = 0; row < terminalManager_->numRows(); ++row) {
      for (int col = 0; col < terminalManager_->numCols(); ++col) {
        if (rand() % 5 == 0) {
          actlStPtr_[row * terminalManager_->numCols() + col] = true;
        } else {
          actlStPtr_[row * terminalManager_->numCols() + col] = false;
        }
      }
    }
  } else if (userInput.isKeyQ()) {
    return false;
  } else if (userInput.isKeyS()) {
    updateState();
  } else if (userInput.isKeyG()) {
    actlStPtr_[1] = true;
    actlStPtr_[terminalManager_->numCols() + 2] = true;
    actlStPtr_[2 * terminalManager_->numCols()] = true;
    actlStPtr_[2 * terminalManager_->numCols() + 1] = true;
    actlStPtr_[2 * terminalManager_->numCols() + 2] = true;
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
          (nCol >= 0 && nCol < terminalManager_->numCols())) {
        if (actlStPtr_[nRow * terminalManager_->numCols() + nCol]) {
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
    for (int col = 0; col < terminalManager_->numCols(); ++col) {
      int neighbors_ = numAliveNeighbors(row, col);
      if (actlStPtr_[row * terminalManager_->numCols() + col] &&
          (neighbors_ == 2 || neighbors_ == 3)) {
        nxtStPtr_[row * terminalManager_->numCols() + col] = true;
      } else if (actlStPtr_[row * terminalManager_->numCols() + col] == false &&
                 neighbors_ == 3) {
        nxtStPtr_[row * terminalManager_->numCols() + col] = true;
      } else {
        nxtStPtr_[row * terminalManager_->numCols() + col] = false;
      }
    }
  }
  bool *tmp = actlStPtr_;
  actlStPtr_ = nxtStPtr_;
  nxtStPtr_ = tmp;
}
