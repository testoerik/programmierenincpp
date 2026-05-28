#include "GameOfLife.h"
#include <unistd.h>

int main() {
  initTerminal();
  initGame();
  TerminalManager terminalManager;
  while (true) {
    UserInput userInput = terminalManager.getUserInput();
    if (processUserInput(userInput) == false) {
      break;
    }
    if (stateGame == true) {
      updateState();
    }
    showState();
    usleep(50'000);
  }
  endwin();
}
