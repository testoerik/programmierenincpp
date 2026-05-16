#include "NcursesDemo.h"
#include <ncurses.h>

// _____________________________________________________________________________
int row;
int col;

// _____________________________________________________________________________
int numRows;
int numCols;

// _____________________________________________________________________________
const int MAX_NUM_PIXELS = 10'000;
bool pixels[MAX_NUM_PIXELS] = {0};

// _____________________________________________________________________________
void startNcurses() {
  initscr();
  numRows = LINES;
  numCols = COLS / 2;
  if (numRows * numCols > MAX_NUM_PIXELS) {
    endwin();
    printf("Too many pixels: %d\n", numRows * numCols);
    return;
  }
  curs_set(false);
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLUE);
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
}

// ____________________________________________________________________________
void endNcurses() { endwin(); }

// ____________________________________________________________________________
bool processMouseEvent(int keycode) {
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
void setPixel(int row, int col, bool value) {
  pixels[row * numCols + col] = value;
}

// ___________________________________________________________________________
bool getPixel(int row, int col) { return pixels[row * numCols + col]; }

// ___________________________________________________________________________
void drawAllPixels() {
  attron(COLOR_PAIR(1));
  for (int row = 0; row < numRows; ++row) {
    for (int col = 0; col < numCols; ++col) {
      bool pixelValue = getPixel(row, col);
      if (pixelValue) {
        attron(A_REVERSE);
      }
      mvprintw(row, 2 * col, "  ");
      if (pixelValue) {
        attroff(A_REVERSE);
      }
    }
  }
  attroff(COLOR_PAIR(1));
  refresh();
}
