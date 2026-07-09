#include "./BrailleTerminalManager.h"

BrailleTerminalManager::BrailleTerminalManager() {
  for (int i = 0; i < (numRows() * numCols() / 8); i++) {
    vectorOfBraillePixels.insert(i, braillePixel);
  }
}
