// Author Erik Hagmüller

#include "NcursesDemo.h"
#include <ncurses.h>
#include <unistd.h>

int main() {
  startNcurses();

  while (true) {
    int keycode = getch();
    bool mouseClicked = processMouseEvent(keycode);
    if (mouseClicked) {
      setPixel(row, col, !getPixel(row, col));
      drawAllPixels();
    }
    if (keycode != ERR) {
      mvprintw(1, 2, "Mouse clicked at row %3d, col %3d", row, col);
      refresh();
    }
    if (keycode == 27) {
      break;
    }
    usleep(1'000);
  }

  endNcurses();
}
