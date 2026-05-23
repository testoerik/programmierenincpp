#include "GameOfLife.h"
#include <unistd.h>

int main() {
  initTerminal();
  initGame();
  while (true) {
    if (processUserInput(getch()) == false) {
      break;
    }
    if (StateGame == true) {
      updateState();
    }
    ShowState();
    usleep(50'000);
  }
  endwin();
}
