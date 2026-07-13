#include <clocale>
#include <ncurses.h>
#include <string>
int main() {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(false);
  const char *braillePattern = u8"\u28FF";
  mvprintw(1, 1, "%s", braillePattern);
  refresh();
  getch();
  endwin();
  return 0;
}
