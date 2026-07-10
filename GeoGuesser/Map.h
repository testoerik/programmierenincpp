#include "./BrailleTerminalManager.h"
#include <string>
#include <vector>
#pragma once;
struct Point {
  int longitude_; // längengrad / col / x.
  int latitude_;  // breitengrad / row / y.
};
class Map : public TerminalManager {
public:
  void readPointsFromFile(const std::string &filename);
  std::vector<Point> containerOfPoints_;

  void computeMap(); /* 1) berechne die Position im Container, an der sich der
                        Pnkt befindet. 2) berechne die Position im Array,
                        welches ein 2 x 4 Feld repräsentiert.*/
  void drawMap();    // Zeichne die Karte.

private:
  Point parsePoint(const std::string &input) const;
};
