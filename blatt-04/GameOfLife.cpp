#include <GameOfLife.h>
#include <ncurses.h>

bool* a = actualState[];
bool* n = nextState[];


// ___________________________________________________________________________
const int MAX_NUM_CELLS = 10'000;

// ---------------------------------------------------------------------------
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
}
