#include "./MockTerminalManager.h"

MockTerminalManager::MockTerminalManager(int a, int b) {
  numRows_ = a;
  numCols_ = b;
}
void MockTerminalManager::drawPixel(int row, int col, bool inverse,
                                    float intensity) override {
  for (const auto &b : heatMap())
}
bool MockTerminalManager::isPixelDrawn(int row, int col) {
        if (
}
