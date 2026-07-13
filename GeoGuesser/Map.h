#include "./BrailleTerminalManager.h"
#include <string>
#include <vector>
#pragma once;
struct Point {
  float longitude_; // längengrad / col / x.
  float latitude_;  // breitengrad / row / y.
};
class Map {
public:
  
  void readPointsFromFile(const std::string &filename);

  void computeMap(); /* 1) berechne die Position im Container, an der sich der
                        Pnkt befindet. 2) berechne die Position im Array,
                        welches ein 2 x 4 Feld repräsentiert.*/
  void drawMap();    // Zeichne die Karte.
  // Getter-Funktion für die Punkte, die aus dem Dateiobjekt ausgelesen wurden.
  std::vector<Point> &points() { return points_; }
private:
  Point parsePoint(const std::string &input) const;
  std::vector<Point> points_;
};
