#include "GameOfLife.h"
#include <unistd.h>

int main() {
  initTerminal();
  initGame();
  while (true) {
    if (processUserInput(getch())) {
      if (StateGame) {
        updateState();
        showState();
        usleep(50'000);
      } else {
        continue;
      }
    } else {
      break;
    }
  }
}
