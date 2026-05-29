#include "GameOfLife.h"
#include <unistd.h>

int main() {
  TerminalManager terminalManager;
  GameOfLife gameOfLife;
  GameOfLife gameOfLife(&terminalManager);
  gameOfLife.play();
};
