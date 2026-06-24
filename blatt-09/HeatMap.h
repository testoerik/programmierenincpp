#pragma once
#include "./TerminalManager.h"
#include <string>
#include <vector>

struct Point {
  //.
  float longitude_;
  float latitude_;
};

class HeatMap {
public:
  auto points();
  void readPointsFromFile(const std::string &filename);
  std::vector<Point> vOfpoints_;
};
