#include <GameOfLife.h>
#include <ncurses.h>

// ---------------------------------------------------------------------------
void initTerminal() {
  initscr();
  cbreak();
  noecho();
  curse_set(false);
  nodelay(stdscr, true);
  keypad(stdscr, false);

  start_color();
}
