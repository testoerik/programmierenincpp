#include "./MockTerminalManager.h"

MockTerminalManager::MockTerminalManager(int a, int b) {
  numRows_ = a;
  numCols_ = b;
}
void MockTerminalManager::drawPixel(int row, int col, bool inverse,
                                    float intensity) override {
  PairIntensBool pairIntensBool;
  if (inverse) {
    pairIntensBool.intensity_ = intensity;
    pairIntensBool.isPixel_ = true;
    unordMap[row * numCols + col] = pairIntensBool;
  }
  bool MockTerminalManager::isPixelDrawn(int row, int col) {
        if (unordMap.at(row * numCols + col) {
      return true;
	} else {
      return false;
	}
  }
