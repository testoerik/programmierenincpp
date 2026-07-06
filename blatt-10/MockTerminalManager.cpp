#include "./MockTerminalManager.h"

MockTerminalManager::MockTerminalManager(int a, int b) {
  numRows_ = a;
  numCols_ = b;
}
void MockTerminalManager::drawPixel(int row, int col, bool inverse,
                                    float intensity) {
  PairIntensInverse pairIntensBool;
  pairIntensBool.intensity_ = intensity;
  pairIntensBool.inverse_ = inverse;
  unordMap[row * numCols_ + col] = pairIntensBool;
}
bool MockTerminalManager::isPixelDrawn(int row, int col) {
  return unordMap[row * numCols_ + col].inverse_;
}
bool MockTerminalManager::isPixelInverse(int row, int col) {
  return unordMap[row * numCols_ + col].inverse_;
}
float MockTerminalManager::getIntensity(int row, int col) {
  int key = row * numCols_ + col;
  PairIntensInverse pairIntensBool = unordMap[key];
  return pairIntensBool.intensity_;
}

void MockTerminalManager::refresh() {}
