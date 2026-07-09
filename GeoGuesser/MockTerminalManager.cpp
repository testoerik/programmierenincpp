#include "./MockTerminalManager.h"

// ______________________________________________________________________
void MockTerminalManager::drawPixel(int row, int col, int color) {
  // This also "draws" Pixels that are outside of the screen, but this
  // behavior is consistent with NCurses which also does not crash
  // in this case.
  drawnPixels_[Cell(row, col)] = color;
}

// _________________________________________________________________________
bool MockTerminalManager::isPixelDrawn(int row, int col) const {
  return drawnPixels_.count(Cell(row, col));
}

// _________________________________________________________________________
int MockTerminalManager::getColor(int row, int col) const {
  return drawnPixels_.at(Cell(row, col));
}
