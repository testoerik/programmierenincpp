#include "./Map.h"
#include <ifstream>

Point Map::parsePoint(const std::string &input) const {
  size_t pos1 = input.find('(');
  size_t pos2 = input.find(' ', pos1 + 1);

  int lon = atoi(input.data() + pos1 + 1);
  int lat = atoi(input.data() + pos2 + 1);
  return Point{lon, lat};
}

void Map::readPointsFromFile(const std::string &filename) {
  // Construct of ifstream class ?
  // Dateiobjekt anlegen und initialisieren.
  /* Gleichwertig dazu wäre:
          std::ifstream datei;
          datei.open(pfad / filename);*/
  std::ifstream pointsFile(filename);
  std::string line;
        while (std::getline(pointsFile, line)) {
		}
}
