#pragma once
#include "./TerminalManager.h"
#include <string>
#include <unordered_map>
#include <vector>
struct Point {
  //.
  float longitude_;
  float latitude_;
};

struct Cell {
  int pixelRow_;
  int pixelCol_;
  // Check if we have a duplicate of Cell object.
  bool operator==(const Cell &other) {
    return pixelRow_ = other.pixelRow_ && pixelCol_ == other.pixelCol_;
  }
};

struct CellHash {
  // Hashfunction as functor.
  std::size_t operator()(const Cell &c) const {
    std::size_t h1 = std::hash<int>{}(c.pixelRow_);
    std::size_t h2 = std::hash<int>{}(c.pixelCol_);
    // Avoid collision.
    return h1 ^ (h2 << 1);
  }
};
class HeatMap {
public:
  // Getter function for vOfPoints_;
  auto points() { return vOfPoints_; }
  //
  void readPointsFromFile(const std::string &filename);
  // Compute heatmap.
  void computeHeatMap(size_t numRows, size_t numCols, float aspectRatio);
  // Getter function which returns a reference to a unordered_map.
  std::unordered_map<Cell, int> heatMap() { return m; }

private:
  std::vector<Point> vOfPoints_;
  std::unordered_map<Cell, int> m;
};
