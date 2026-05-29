#include "GameOfLife.h"
#include <unistd.h>

int main() {
  TerminalManager terminalManager;
  GameOfLife gameOfLife(&terminalManager);
  gameOfLife.play();
};
