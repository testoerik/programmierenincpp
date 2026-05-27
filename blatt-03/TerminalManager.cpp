#include "./TerminalManager.h"
#include <ncurses.h>
// ___________________________________________________________________________
int TerminalManager::Red = COLOR_RED;
int TerminalManager::Green = COLOR_GREEN;

void TerminalManager::setup() {
  // Initialize ncurses and some settings suitable for our game.
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, true);

  // Initialize the colors we need for the game.

  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  // Set the logical dimensions of the screen.
  numRows_ = LINES;
  numCols_ = COLS / 2;
}

void TerminalManager::drawPixel(int row, int col, int color) {
  if (color == COLOR_GREEN) {
    attron(COLOR_PAIR(1));
  }
  attron(A_REVERSE);
  mvprintw(row, 2 * col, "  ");
}
UserInput TerminalManager::getUserInput() {
  UserInput userInput;
  userInput.keycode_ = getch();
  return userInput;
}
void TerminalManager::cleanup() { endwin(); }
void TerminalManager::refresh() { ::refresh(); }

bool UserInput::isEscape() { return keycode_ == 27; }
bool UserInput::isKeyUp() { return keycode_ == KEY_UP; }
bool UserInput::isKeyDown() { return keycode_ == KEY_DOWN; }
bool UserInput::isKeyRight() { return keycode_ == KEY_RIGHT; }
bool UserInput::isKeyLeft() { return keycode_ == KEY_LEFT; }
