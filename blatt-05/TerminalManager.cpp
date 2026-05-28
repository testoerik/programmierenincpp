#include "./TerminalManager.h"
#include <ncurses.h>

// ____________________________________________________________________________
int TerminalManager::White = COLOR_WHITE;
int TerminalManager::Red = COLOR_RED;
int TerminalManager::Green = COLOR_GREEN;

// ____________________________________________________________________________
TerminalManager::TerminalManager() {
  // Initialize ncurses and some settings suitable for our game.
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

// _____________________________________________________________________________
void TerminalManager::drawPixel(int row, int col, int color) {
  if (color == COLOR_WHITE) {
    attron(COLOR_PAIR(1));
  } else if (color == COLOR_RED) {
    attron(COLOR_PAIR(2));
  } else if (color == COLOR_GREEN) {
    attron(COLOR_PAIR(3));
  }
  attron(A_REVERSE);
  mvprintw(row, 2 * col, "  ");
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
bool UserInput::isKeySpace() { return keycode_ == '  '; }
bool UserInput::isKeyMouse() { return keycode_ == KEY_MOUSE; }
// _____________________________________________________________________________
TerminalManager::~TerminalManager() { endwin(); }
