#include "Snake.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  startNcurses();
  initTerminal();
  initGame();
  while (true) {
    clear();
    drawBorder();
    drawSnake();
    for (int i, i <= 10'000, ++i) {
      int key = getch();
      if (key != ERR) {
        mvprintw(2, 2, "Key: %3d", key);
        refresh();
      }
      if (handleKey(key) {
        break;
	}
      moveSnake();
      if (collidesWithBorder()) {
        break;
	}
    }
  }
}
