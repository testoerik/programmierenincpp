#include "GameOfLife.h"
#include <unistd.h>

int main() {
  TerminalManager terminalManager;
  GameOfLife gameOfLife(terminalManager.numRows(), terminalManager.numCols(),
                        &terminalManager);
  gameOfLife.play();
};
