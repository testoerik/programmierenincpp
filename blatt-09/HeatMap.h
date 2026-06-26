#pragma once
#include "./Cell.h"
#include "./TerminalManager.h"
#include <string>
#include <unordered_map>
#include <vector>
struct Point {
  //.
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
  // Getter function which returns a reference to a unordered_map.
  std::unordered_map<Cell, int, CellHash> heatMap() { return m; }

private:
  std::vector<Point> vOfPoints_;
  std::unordered_map<Cell, int, CellHash> m;
};
