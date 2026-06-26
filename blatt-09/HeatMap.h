#pragma once
#include "./TerminalManager.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "./Cell.h"
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

private:
  std::vector<Point> vOfPoints_;
};
