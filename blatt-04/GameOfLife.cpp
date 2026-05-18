#include "GameOfLife.h"
#include <ncurses.h>

int dimX;
int dimY;

int numRows;
int numCols;

// ___________________________________________________________________________
const int MAX_NUM_CELLS = 10'000;
bool actualState[MAX_NUM_CELLS] = {0};
bool nextState[MAX_NUM_CELLS];

// ___________________________________________________________________________
bool *a = actualState[];
bool *n = nextState[];

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
  posX = dimX / 2;
  posY = dimY / 2;
  for (int i = 0; i < MAX_NUM_CELLS; ++i) {
    actualState[i] = false;
  }
  StateGame = false;
  numAliveCells = 0;
}
// ___________________________________________________________________________

void ShowState() {
  start_color() attron(color_pair(1));
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols, ++col) {
      cellValue = actualState[row * numCols + col];
      if (cellValue) {
        attron(A_REVERSE);
      }
      mvprint(row, 2 * col, "  ");
      if (cellValue) {
        attroff(A_REVERSE)
      }
    }
  }
  attroff(color_pair(1));
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

int numAliveNeighbor(int row, int col) {
  int aliveCount = 0;
  if (((row - 1) <= 0 && (row + 1) < dimY) &&
      ((col - 1) <= 0 && (col + 1)) < dimX) {
    endwin();
                printf("Too many pixel": %d\n");
		return;
  }
}
