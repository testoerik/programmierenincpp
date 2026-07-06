#include "./MockTerminalManager.h"

MockTerminalManager::MockTerminalManager(int a, int b) {
  numRows_ = a;
  numCols_ = b;
}
void MockTerminalManager::drawPixel(int row, int col, bool inverse,
                                    float intensity) {
  PairIntensBool pairIntensBool;
  if (inverse) {
    pairIntensBool.intensity_ = intensity;
    pairIntensBool.isPixel_ = true;
    unordMap[row * numCols_ + col] = pairIntensBool;
  }
}
bool MockTerminalManager::isPixelDrawn(int row, int col) {
  if (unordMap.count(row * numCols_ + col) >= 1) {
    return true;
  } else {
    return false;
  }
}
bool MockTerminalManager::isPixelInverse(int row, int col) { return true; }
float MockTerminalManager::getIntensity(int row, int col) {
  int key = row * numCols_ + col;
  PairIntensBool pairIntensBool = unordMap[key];
  return pairIntensBool.intensity_;
}

void MockTerminalManager::refresh() {}
