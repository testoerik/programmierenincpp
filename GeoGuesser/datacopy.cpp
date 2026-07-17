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
  string objectCoordinates = input.substr(input.find('\t') + 1);
  replace(objectCoordinates.begin(), objectCoordinates.end(), '(', ' ');
  replace(objectCoordinates.begin(), objectCoordinates.end(), ')', ' ');
  replace(objectCoordinates.begin(), objectCoordinates.end(), ' ', ' ');
  stringstream coordinates(objectCoordinates);
  float lon;
  float lat;
  vector<Point> v1;
  while (coordinates >> lon >> lat) {
	Point p1{lon, lat};
	v1.push_back(p1);
  }
  return v1;
}

int main() {
  string line;
  ifstream pointsFile("./tf-buildings.tsv");
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
