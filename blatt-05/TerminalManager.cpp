#include "./TerminalManager.h"
#include <ncurses.h>

// ____________________________________________________________________________
int TerminalManager::White = COLOR_WHITE;
int TerminalManager::Blue = COLOR_BLUE;
// ____________________________________________________________________________
TerminalManager::TerminalManager() {
  // Initialize ncurses and some settings suitable for our game.
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);
  mousemask(ALL_MOUSE_EVENTS, NULL);
  mouseinterval(0);
  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLUE);

  numRows_ = LINES;
  numCols_ = COLS / 2;
}

// _____________________________________________________________________________
void TerminalManager::drawPixel(int row, int col, int color) {
  if (color == COLOR_WHITE) {
    attron(COLOR_PAIR(1) | A_REVERSE);
    mvprintw(row, 2 * col, "  ");
    attroff(A_REVERSE);
  } else {
    attron(COLOR_PAIR(1));
    mvprintw(row, 2 * col, "  ");
  }
}

// _____________________________________________________________________________
void TerminalManager::refresh() { ::refresh(); }

// _____________________________________________________________________________
UserInput TerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  return userInput;
}

// _____________________________________________________________________________
bool UserInput::isKeyQ() { return keycode_ == 'q'; }
bool UserInput::isKeyG() { return keycode_ == 'g'; }
bool UserInput::isKeyR() { return keycode_ == 'r'; }
bool UserInput::isKeyS() { return keycode_ == 's'; }
bool UserInput::isKeySpace() { return keycode_ == 32; }
bool UserInput::isKeyMouse() { return keycode_ == KEY_MOUSE; }
int UserInput::eventX() {
  MEVENT event;
  return event.x / 2;
}
int UserInput::eventY() {
  MEVENT event;
  return event.y;
}

// _____________________________________________________________________________
TerminalManager::~TerminalManager() { endwin(); }
