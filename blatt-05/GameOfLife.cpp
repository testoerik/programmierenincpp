#include "GameOfLife.h"
#include <cstdlib>
#include <ncurses.h>

// ___________________________________________________________________________
const int MAX_NUM_CELLS = 10'000;
bool actualState[MAX_NUM_CELLS] = {0};
bool nextState[MAX_NUM_CELLS];
GameOfLife::play() {
  
  while (true) {
    UserInput userInput = terminalManager.getUserInput();
    if (processUserInput(userInput) == false) {
      break;
    }
    if (stateGame == true) {
      updateState();
    }
    showState();
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
GameOfLife::ShowState() {
  start_color();
  attron(COLOR_PAIR(1));

  numAliveCells = 0;

  for (int row = 0; row < numRows - 1; ++row) {
    for (int col = 0; col < numCols; ++col) {
      bool cellValue = a[row * numCols + col];
      if (cellValue) {
        numAliveCells += 1;
        attron(A_REVERSE);
      }
      mvprintw(row, 2 * col, "  ");
      if (cellValue) {
        attroff(A_REVERSE);
      }
    }
  }
  attron(A_REVERSE);
  mvprintw(numRows - 1, 0, "Alive Cells: %d", numAliveCells);
  attroff(A_REVERSE);
  attroff(COLOR_PAIR(1));
  refresh();
}

// ___________________________________________________________________________
GameOfLife::processUserInput(UserInput userInput) {
  if (userInput.isKeyMouse()) {
    MEVENT event;
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_PRESSED) {
        row = event.y;
        col = event.x / 2;
        a[row * numCols + col] = !a[row * numCols + col];
      }
    }
  } else if (userInput.isKeySpace()) {
    stateGame = !stateGame;
  } else if (userInput.isKeyR()) {
    for (int row = 0; row < numRows; ++row) {
      for (int col = 0; col < numCols; ++col) {
        if (rand() % 5 == 0) {
          a[row * numCols + col] = true;
        } else {
          a[row * numCols + col] = false;
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
    if ((row >= 0 && row + 2 < numRows) && (col >= 0 && col + 2 < numCols)) {
      a[row * numCols + (col + 1)] = true;
      a[(row + 1) * numCols + (col + 2)] = true;
      a[(row + 2) * numCols + (col + 0)] = true;
      a[(row + 2) * numCols + (col + 1)] = true;
      a[(row + 2) * numCols + (col + 2)] = true;
    }
  }
  return true;
}

// ___________________________________________________________________________
GameOfLife::numAliveNeighbors(int row, int col) {
  int aliveCount = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int nRow = row + i;
      int nCol = col + j;
      if (i == 0 && j == 0) {
        continue;
      }
      if ((nRow >= 0 && nRow < numRows) && (nCol >= 0 && nCol < numCols)) {
        if (a[nRow * numCols + nCol]) {
          aliveCount += 1;
        }
        continue;
      }
    }
  }
  return aliveCount;
}
// ___________________________________________________________________________
GameOfLife::updateState() {
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      int neighbors = numAliveNeighbors(row, col);
      if (a[row * numCols + col] && (neighbors == 2 || neighbors == 3)) {
        n[row * numCols + col] = true;
      } else if (a[row * numCols + col] == false && neighbors == 3) {
        n[row * numCols + col] = true;
      } else {
        n[row * numCols + col] = false;
      }
    }
  }
  bool *tmp = a;
  a = n;
  n = tmp;
}
