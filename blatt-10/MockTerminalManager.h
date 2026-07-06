#pragma once
#include "./TerminalManager.h"
#include <unordered_map>
#include <vector>

struct PairIntensBool {
  float intensity_;
  bool isPixel_;
  bool operator==(const PairIntensBool &other) {
    return other.intensity_ == intensity_ && other.isPixel_ == isPixel_;
  }
};
template <> struct std::hash<PairIntensBool> {
  size_t operator()(const PairIntensBool &p) const {
    auto hash1 = std::hash<size_t>{}(p.intensity_);
    auto hash2 = std::hash<size_t>{}(p.isPixel_);
    return 2 * hash1 ^ hash2;
  }
};
class MockTerminalManager : public TerminalManager {
public:
  // Constructor.
  MockTerminalManager(int a, int b);
  // Checks whether the pixel is drawn or not.
  bool isPixelDrawn(int row, int col);
  void drawPixel(int row, int col, bool inverse, float intensity) override;
  void refresh() override;
  bool isPixelInverse(int row, int col);
  float getIntensity(int row, int col);

protected:
  std::unordered_map<int, PairIntensBool> unordMap;
};
