#include "GameOfLife.h"
#include <cstdlib>

void GameOfLife::play() {
  
  while (true) {
    UserInput userInput = terminalManager_->getUserInput();
    if (processUserInput(userInput) == false) {
      break;
    }
    if (stateGame == true) {
      updateState();
    }
    terminalManager_->showState();
    usleep(50'000);
  }
  endwin();
}
// ___________________________________________________________________________
GameOfLife::GameOfLife(TerminalManager *terminalManager) {
  terminalManager_ = terminalManager;

  int cols_ = terminalManager_->numCols_;
  int rows_ = terminalManager_->numRows_;
  posX_ = cols_ / 2;
  posY_ = rows_ / 2;
  // Clean actualState and nextState.
  for (int i = 0; i < MAX_NUM_CELLS; ++i) {
    actualState_[i] = false;
    nextState_[i] = false;
  }

  // Update both a and n because a or n could contain garbage.
  actlStPtr_ = actualState_;
  nxtStPtr_= nextState_;
  stateGame_ = false;
  numAliveCells_ = 0;
}


// ___________________________________________________________________________
bool GameOfLife::processUserInput(UserInput userInput) {
  if (userInput.isKeyMouse()) {
    MEVENT event;
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_PRESSED) {
        row_ = event.y;
        col_ = event.x / 2;
        a[row_ * numCols_ + col_] = !a[row_ * numCols_ + _col];
      }
    }
  } else if (userInput.isKeySpace()) {
    stateGame_ = !stateGame_;
  } else if (userInput.isKeyR()) {
    for (int row_ = 0; row_ < numRows_; ++row_) {
      for (int col_ = 0; col_ < numCols_; ++col_) {
        if (rand() % 5 == 0) {
          a[row_ * numCols_ + col_] = true;
        } else {
          a[row_ * numCols_ + col_] = false;
        }
      }
    }
  } else if (userInput.isKeyQ()) {
    endwin();
    printf("Game ended");
    return false;
  } else if (userInput.isKeyS()) {
    updateState();
  } else if (userInput.isKeyG()) {
    if ((row_ >= 0 && row_ + 2 < numRows_) && (col_ >= 0 && col_ + 2 < numCols_)) {
      a[row_ * numCols_ + (col_ + 1)] = true;
      a[(row_ + 1) * numCols_ + (col_ + 2)] = true;
      a[(row_ + 2) * numCols_ + (col_ + 0)] = true;
      a[(row_ + 2) * numCols_ + (col_ + 1)] = true;
      a[(row_ + 2) * numCols_ + (col_ + 2)] = true;
    }
  }
  return true;
}

// ___________________________________________________________________________
int GameOfLife::numAliveNeighbors(int row_, int col_) {
  int aliveCount_ = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int nRow = row_ + i;
      int nCol = col_ + j;
      if (i == 0 && j == 0) {
        continue;
      }
      if ((nRow >= 0 && nRow < numRows_) && (nCol >= 0 && nCol < numCols_)) {
        if (a[nRow * numCols_ + nCol]) {
          aliveCount_ += 1;
        }
        continue;
      }
    }
  }
  return aliveCount_;
}
// ___________________________________________________________________________
void GameOfLife::updateState() {
  for (int row_ = 0; row_ < numRows; ++row_) {
    for (int col_ = 0; col_ < numCols; ++col_) {
      int neighbors_ = numAliveNeighbors(row_, col_);
      if (a[row_ * numCols_ + col_] && (neighbors_ == 2 || neighbors_ == 3)) {
        n_[row_ * numCols_ + col_] = true;
      } else if (a_[row_ * numCols_ + col_] == false && neighbors_ == 3) {
        n_[row_ * numCols_ + col_] = true;
      } else {
        n_[row_ * numCols_ + col_] = false;
      }
    }
  }
  bool *tmp = a_;
  a_ = n_;
  n_ = tmp;
}
