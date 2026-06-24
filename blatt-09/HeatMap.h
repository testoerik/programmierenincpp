#pragma once
#include "./TerminalManager.h"
#include <string>
class HeatMap {
public:
  void readPointsFromFile(const std::string &filename);
};

struct Point {}
