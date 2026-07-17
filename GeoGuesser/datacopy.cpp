#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
  float longitude_; // längengrad, col, x-Achse
  float latitude_;  // breitengrad, row, y-Achse
};

vector<Point> parseLine(const string &input) {
  
  string objectName = input.substr(0, input.find('\t'));
  size_t start = input.find('\t') + 1;
  string objectCoordinates = input.substr(start);
  
  size_t posOpenBracket = objectCoordinates.find_first_of('(');
  objectCoordinates = objectCoordinates.substr(posOpenBracket);
  cout << objectCoordinates;
  size_t end = input.find_last_of('"');
  replace(objectCoordinates.begin(), objectCoordinates.end(), '(', ' ');
  replace(objectCoordinates.begin(), objectCoordinates.end(), ')', ' ');
  replace(objectCoordinates.begin(), objectCoordinates.end(), ',', ' ');
  float lon;
  float lat;
  vector<Point> v1;
  cout << objectCoordinates << '\n';
  stringstream coordinates(objectCoordinates);
  while (coordinates >> lon >> lat) {
	Point p1{lon, lat};
	v1.push_back(p1);
  }
  return v1;
}

int main() {
  string line;
  ifstream pointsFile("./tf-buildings.tsv");
  if (!pointsFile.is_open()) {
	cout << "Fehler" << '\n';
  }
  vector<vector<Point>> vectorPoints;
  cout << line;
  while (getline(pointsFile, line)) {
    vectorPoints.push_back(parseLine(line));
  }
  for (auto &vec : vectorPoints) {
	for (auto &points : vec) { 
		cout << points.longitude_ << '\n' << points.latitude_ << '\n';
	}
  }
}
