#include "./Map.h"
#include <ifstream>

Point Map::parsePoint(const std::string &input) const {
  size_t pos1 = input.find('(');
  size_t pos2 = input.find(')');

  std::string line = input.substr(pos1, pos2);
  
  // Jetzt müssen wir noch die öffnenden Klammern am Anfang entfernen.
  std::string s1 = "";
  for (int i = 0; i < input.length(); ++i) {
	if (input[i] == '(') {
		continue;
	} else {
		s1 += input[i];
	}
  }
  std::string lon = "";
  std::string lat = "" 
  // Jetzt müssen wir die Längen -und Breitengrad aus dem String extrahieren.
  for (int i = 0; i < s1.length(); ++i) {
	if (s1[i] != " ") {
   	// lon aber noch als String.
	lon += s1[i];
	} else if (s1[i] != ", ") {
	   lat += s[i];
	} else {
	  Point point;
	  point.longitude_ = std::atof(lon);
	  point.latitude_ = std::atof(lat);
	  lon = 
  }
  
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
    points_.push_back(line);
  }
}
void Map::computeMap(size_t row, size_t col, 1.0f) {
 	/* Unser Vektor hat (AnzahlZeile * AnzahlSpalte) Blöcke die jeweils 2 Spalten mal 4 Zeilen groß sind. Jeder Block ist daher ein Array der größe 8 und hat einen bestimmten Index in unserem Vektor. Dabei nutzen wir den /-Operator aus.Wir führen zudem die gleiche Rechung durch, die wir für unser Snake-Spiel durchgeführt haben. Nämlich "reduzieren" wir unseren 2D-Bildschirm auf eine 1D-Liste. */	
        size_t indexVector = (row * numCols + col) / 8;
/* Jetzt müssen wir noch herausfinden, an welcher Stelle sich der Punkt in unserem Array befindet. Wir wollen den Braille Zeichen gegenüber konsistent bleiben.*/
        size_t indexArray = (row * numCols + col);
}
