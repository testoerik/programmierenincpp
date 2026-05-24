
#include "./TerminalManager.h"

void TerminalManager::setup() {
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);

  // Initialize all the colors we need for the game.
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);

  // Set the logical dimensions of the screen.
  numRows_ = LINES;
  numCols_ = COLS / 2;
}

void TerminalManager::drawPixel(int row, int column, int color) {
  attron(COLOR_PAIR(color) | A_REVERSE);
  mvprintw(row, column, "  ");
  attroff(COLOR_PAIR(color));
  attroff(A_REVERSE);
}
