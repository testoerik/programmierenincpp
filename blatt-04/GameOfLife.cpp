#include "GameOfLife.h"
#include <ncurses.h>

int numRows;
int numCols;
int posX;
int posY;
int row;
int col;
int numAliveCells;
bool StateGame;

// ___________________________________________________________________________
const int MAX_NUM_CELLS = 10'000;
bool actualState[MAX_NUM_CELLS] = {0};
bool nextState[MAX_NUM_CELLS];

// ___________________________________________________________________________
bool *a = actualState;
bool *n = nextState;

// ___________________________________________________________________________
void initTerminal() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, false);
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  start_color();

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  numCols = COLS / 2;
  numRows = LINES;
}

// ___________________________________________________________________________
void initGame() {
  posX = numCols / 2;
  posY = numRows / 2;
  for (int i = 0; i < MAX_NUM_CELLS; ++i) {
    actualState[i] = false;
  }
  StateGame = false;
  numAliveCells = 0;
}

// ___________________________________________________________________________
void ShowState() {
  start_color();
  attron(COLOR_PAIR(1));
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      bool cellValue = actualState[row * numCols + col];
      if (cellValue) {
        attron(A_REVERSE);
      }
      mvprintw(row, 2 * col, "  ");
      if (cellValue) {
        attroff(A_REVERSE);
      }
    }
  }
  attroff(COLOR_PAIR(1));
  return;
}
// ___________________________________________________________________________
bool processUserInput(int keycode) {
  if (keycode == KEY_MOUSE) {
    MEVENT event;
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_PRESSED) {
        row = event.y;
        col = event.x / 2;
        return true;
      }
    }
  }
  return false;
}

// ___________________________________________________________________________
int numAliveNeighbors(int row, int col) {
  int aliveCount = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      int nRow = row + i;
      int nCol = col + j;
      if (i == 0 && j == 0) {
        continue;
      }
      if (nRow >= 0 && nRow < numRows && nCol >= 0 && nCol < numCols) {
        if (a[nRow * numCols + nCol]) {
          aliveCount += 1;
        }
        continue;
      }
    }
    return aliveCount;
  }
}

// ___________________________________________________________________________
void updateState() {
  for (int row = 0; rol < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      int neighbors = numAliveNeighbor(row, col);
      if (a[row * numCols + col] && neighbors == 2 || neighbors == 3) {
        bool n[row * numCols + col] = true;
      } else if (a[row * numCols + col] == false && neighbors == 3) {
        bool n[row * numCols + col] == true;
      } else {
        bool n[row * numCols + col] == false;
      }
    }
  }
  bool *tmp = a;
  a = n;
  n = tmp;
}
