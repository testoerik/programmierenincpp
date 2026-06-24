#include <HeatMap.h>
#include <fstream>

HeatMap::readPointsFromFile(const std::string &filename) {
  // Open the file.
  std::ifstream file(filename);
  // Path to file could be wrong.
  if (!file) {
    std::cout << "The file cannot be opened !" << std::endl;
    exit(1);
  }
  std::string line;
  std::getline(file, line);
}
