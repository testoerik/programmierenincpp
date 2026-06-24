#pragma once
#include "./TerminalManager.h"
#include <string>
#include <vector>

class HeatMap {
public:
  void readPointsFromFile(const std::string &filename);
  std::vector<Point> points_;
};

struct Point {
  //.
  float longitude_;
  float latitude_;
};
