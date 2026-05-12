#include "Snake.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  initTerminal();
  initGame();
  double speed = 5.0;
  double acceleration = 0.5;

  clear();
  drawBorder(1);
  drawSnake(2);
  refresh();

  while (true) {
    int sleep_time_us = 1'000'000 / speed;
    usleep(sleep_time_us);
    int key = getch();
    if (key != ERR) {
      if (handleKey(key)) {
        break;
      }
    }
    moveSnake();
    if collidesWithBorder () {
      break;
    }
    clear();
    drawBooder(1);
    drawSnake(2);
    refresh();

    speed += acceleration * (sleep_time_us / 1'000'000.0);
  }
  mvprintw(LINES / 2, (COLS / 2) - 5, "GAME OVER!");
  mvprintw((LINES / 2) + 1, (COLS / 2) - 10, "Press ESC to exit...");
  refresh();

  while (true) {
    if (getch() == 27) {
      break;
    }
    uslepp(1000);
    endwin();
  }
}
