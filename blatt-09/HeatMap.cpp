#include "./HeatMap.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

void HeatMap::readPointsFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "The file cannot be opened !" << std::endl;
    exit(1);
  }
  std::string line;
  while (std::getline(file, line)) {
    size_t posFirstX = (line.find('(') + 1);
    size_t posLastX = (line.find(',') - 1);
    float pointX = stof(line.substr(posFirstX, (posLastX - posFirstX)));

    size_t posFirstY = (line.find(',') + 2);
    size_t posLastY = (line.find(')') - 1);
    float pointY = stof(line.substr(posFirstY, (posLastY - posFirstY)));

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

  float maxPixelWidth = numCols - 1;
  float maxPixelHeight = numRows - 1;

  float mappedWidth = maxPixelWidth;
  float mappedHeight = mappedWidth * aspectRatio;
  if (mappedHeight > maxPixelHeight) {
    mappedHeight = maxPixelHeight;
    mappedWidth = mappedHeight * aspectRatio;
  }
  float geoWidth = largestLongitude - smallestLongitude;
  float geoHeight = largestLatitude - smallestLatitude;

  float scaleX = mappedWidth / geoWidth;
  float scaleY = mappedHeight / geoHeight;

  int offsetX = (maxPixelWidth - static_cast<int>(std::round(mappedWidth))) / 2;
  int offsetY =
      (maxPixelHeight - static_cast<int>(std::round(mappedHeight))) / 2;

  for (const auto &point : vOfPoints_) {
    int col =
        std::round(offsetX + (point.longitude_ - smallestLongitude) * scaleX);
    int row =
        std::round(offsetY + (largestLatitude - point.latitude_) * scaleY);

    Cell currentCell{row, col};
    unordMapCell_[currentCell]++;
  }
}

void HeatMap::drawHeatMap(TerminalManager *terminalManager) {
  if (unordMapCell_.empty()) {
    return;
  }
  auto maxIterator = std::max_element(
      unordMapCell_.begin(), unordMapCell_.end(),
      [](const auto &a, const auto &b) { return a.second < b.second; });
  int maxVal = maxIterator->second;

  for (int i = 0; i < terminalManager->numRows(); i++) {
    for (int j = 0; j < terminalManager->numCols(); j++) {
      Cell currentCell{i, j};
      if (unordMapCell_.count(currentCell) > 0) {
        float intensityCell = static_cast<float>(unordMapCell_[currentCell]) /
                              static_cast<float>(maxVal);
        terminalManager->drawPixel(i, j, true, intensityCell);
      } else {
        terminalManager->drawPixel(i, j, false, 0.0);
      }
    }
  }
}
