#pragma once
#include "./TerminalManager.h"
#include <cstddef>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

struct Cell {
  int pixelRow_;
  int pixelCol_;
  bool operator==(const Cell &other) const {
    return pixelRow_ == other.pixelRow_ && pixelCol_ == other.pixelCol_;
  }
};

struct CellHash {
  std::size_t operator()(const Cell &c) const {
    std::size_t h1 = std::hash<int>{}(c.pixelRow_);
    std::size_t h2 = std::hash<int>{}(c.pixelCol_);
    return h1 ^ (h2 << 1);
  }
};
struct Point {
  float longitude_;
  float latitude_;
};
class HeatMap {
public:
  // Getter function for vOfPoints_;
  auto points() { return vOfPoints_; }
  //
  void readPointsFromFile(const std::string &filename);
  // Compute heatmap.
  void computeHeatMap(size_t numRows, size_t numCols, float aspectRatio);
  void drawHeatMap(TerminalManager *);
  std::unordered_map<Cell, int, CellHash> heatMap() { return unordMapCell_; }

private:
  std::vector<Point> vOfPoints_;
  std::unordered_map<Cell, int, CellHash> unordMapCell_;
};
