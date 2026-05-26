#include "./TerminalManager.h"
#include <ncurses.h>
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
    attron(color_pair(1));
  }
  attron(A_REVERSE);
  mvprintw(row, 2 * col, "  ");
}
void UserInput TerminalManager::getUserInput() {
	UserInput userInput;
	userInput.keycode_ = getch();
	return userInput}

bool UserInput::isEscape() { return keycode == 27; }
bool UserInput::isKeyUp() { return keycode == KEY_UP; }
bool UserInput::isKeyDown() { return keycode == KEY_DOWN; }
bool UserInput::isKeyRight() { return keycode == KEY_RIGHT; }
bool UserInput::isKeyLeft() { return keycode == KEY_LEFT; }
 
