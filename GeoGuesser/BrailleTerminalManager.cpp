#include "./BrailleTerminalManager.h"

BrailleTerminalManager::BrailleTerminalManager() {
  // Fill the container with numRow * numCol braille pixel.
  for (int i = 0; i < (numRows() * numCols()); i++) {
    std::array<int, 8> braillePixel = {0, 0, 0, 0, 0, 0, 0, 0};
    containerOfBraillePixels_.push_back(braillePixel);
  }
  for (int j = 0; j < (numRows() * numCols(); j++) {
    for (int k = 0; k < 8; k++) {
    }}
}
