#include "./HeatMap.h"
#include <fstream>
#include <iostream>
#include <string>
HeatMap::void readPointsFromFile(const std::string &filename) {
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
    xCoordinate =
        std::stof(line.substr((line.find('(') + 1), (line.find(' ') - 1)));
    yCoordinate =
        std::stof(line.substr((line.find(' ') + 1), (line.find(')') - 1)));
  }
}
