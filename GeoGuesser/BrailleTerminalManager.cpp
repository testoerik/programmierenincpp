#include "./BrailleTerminalManager.h"

BrailleTerminalManager::BrailleTerminalManager() {
  for (int i = 0; i < (numRows() * numCols()); i++) {
    std::array<int, 8> braillePixel = {0, 0, 0, 0, 0, 0, 0, 0};
    containerOfBraillePixels_.push_back(braillePixel);
  }
}

BrailleTerminalManager::BrailleTerminalManager(std::vector<struct>) {
	// Wir iterieren über jeden Punkt, welcher von map ausgelesen wurde.
	for (size_t i = 0; i < )}
void BrailleTerminalManager::drawPixel(int row, int col, int color) {}
