#include "GameOfLife.h"
#include <ncurses.h>

bool *a = actualState[];
bool *n = nextState[];

int dimX;
int dimY;

// ___________________________________________________________________________
const int MAX_NUM_CELLS = 10'000;
bool actualState[MAX_NUM_CELLS] = {0};
bool nextState[MAX_NUMCELLS];

// ___________________________________________________________________________
const int MAX_NUM_CELLS = 10'000;

// ___________________________________________________________________________
void initTerminal() {
  initscr();
  cbreak();
  noecho();
  curse_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, false);
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  start_color();

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  dimX = COLS / 2;
  dimY = LINES;  
}

// ___________________________________________________________________________
void initGame() {
  posX = dimX / 2;
  posY = dimY / 2;
  StateGame = false;
  numAliveCells = 0;
}

// ___________________________________________________________________________
void ShowState() {}

// ___________________________________________________________________________
bool processUserInput(int keycode) {
  if (keycode == KEY_MOUSE) {
    MEVENT event;
    if (getmouse(&event) == OK) {
      if (event.bstate & BUTTON1_PRESSED) {
        row = event.y;
        col = event.x;
        return true;
      }
    }
  }
  return false;
}
