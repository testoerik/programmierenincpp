#include "./HeatMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
void HeatMap::readPointsFromFile(const std::string &filename) {
  // Open the file.
  std::ifstream file(filename);
  // Path to file could be wrong.
  if (!file) {
    std::cout << "The file cannot be opened !" << std::endl;
    exit(1);
  }
  std::string line;
  while (std::getline(file, line)) {
    // Extracting the coordinates.
    // Extracting x-coordinate.
    size_t posFirstX = (line.find('(') + 1);
    size_t posLastX = (line.find(',') - 1);
    float pointX = stof(line.substr(posFirstX, (posLastX - posFirstX)));
    // Extracting y-coordinate.
    size_t posFirstY = (line.find(',') + 2);
    size_t posLastY = (line.find(')') - 1);
    float pointY = stof(line.substr(posFirstY, (posLastY - posFirstY)));
    // Instantiating point class.
    Point point;
    point.longitude_ = pointX;
    point.latitude_ = pointY;
    vOfPoints_.push_back(point);
  }
}
void HeatMap::computeHeatMap(size_t numRows, size_t numCols,
                             float aspectRatio) {
  auto iteratorPairX = std::minmax_element(vOfPoints_.begin(), vOfPoints_.end(),
                                           [](const Point &a, const Point &b) {
                                             return a.longitude_ < b.longitude_;
                                           });
  float smallestLongitude = iteratorPairX.first->longitude_;
  float largestLongitude = iteratorPairX.second->longitude_;
  auto iteratorPairY = std::minmax_element(
      vOfPoints_.begin(), vOfPoints_.end(),
      [](const Point &a, const Point &b) { return a.latitude_ < b.latitude_; });
  float smallestLatitude = iteratorPairY.first->latitude_;
  float largestLatitude = iteratorPairY.second->latitude_;
}
