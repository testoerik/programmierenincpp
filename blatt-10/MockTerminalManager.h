#pragma once
#include "./TerminalManager.h"
#include <unordered_map>
#include <vector>

class MockTerminalManager : public TerminalManager {
public:
  // Constructor.
  explicit MockTerminalManager(int a, int b);

  // Checks whether the pixel is drawn or not.
  bool isPixelDrawn(int row, int col);
  void drawPixel(int row, int col, bool inverse, float intensity);
  void refresh();

protected:
  std::unordered_map<int, std::vector<float, bool>> unordMap;
};

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
