#include "./NCursesTerminalManager.h"
#include <ncurses.h>

// ____________________________________________________________________________
NCursesTerminalManager::NCursesTerminalManager() {
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  // Catch mouse events
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);

  numColors_ = (COLORS < 16) ? COLORS : 16;
  for (int c = 0; c < numColors_; ++c) {
    init_pair(c + 1, c, COLOR_BLACK);
    init_pair(numColors_ + c + 1, COLOR_BLACK, c);
  }
  numRows_ = LINES;
  numCols_ = COLS / 2;

  // Initialize with background color.
  for (int row = 0; row < numRows_; ++row) {
    for (int col = 0; col < numCols_; ++col) {
      drawPixel(row, col, 0);
    }
  }
}

// ____________________________________________________________________________
NCursesTerminalManager::~NCursesTerminalManager() { endwin(); }

// ____________________________________________________________________________
void NCursesTerminalManager::drawPixel(int row, int col, int color) {
  int pair = numColors_ + color + 1;
  attron(COLOR_PAIR(pair));
  mvprintw(row, 2 * col, "  ");
  attroff(COLOR_PAIR(pair));
}

// ____________________________________________________________________________
void NCursesTerminalManager::refresh() { ::refresh(); }

// ___________________________________________________________________________
void NCursesTerminalManager::drawString(int row, int col, const char *output,
                                        int color) {
  attron(COLOR_PAIR(color + 1));
  mvaddstr(row, 2 * col, output);
  // Clear the rest of the line, s.t. no rest of previous content remains there.
  clrtoeol();
  attroff(COLOR_PAIR(color + 1));
}

// ___________________________________________________________________________
UserInput NCursesTerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  if (userInput.keycode_ == KEY_MOUSE) {
    MEVENT mouseEvent;
    if (getmouse(&mouseEvent) == OK) {
      if (mouseEvent.bstate & BUTTON1_PRESSED) {
        userInput.mouseRow_ = mouseEvent.y;
        userInput.mouseCol_ = mouseEvent.x / 2;
      }
    }
  }
  return userInput;
}
