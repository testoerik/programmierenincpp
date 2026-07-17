#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Point {
  float longitude_; // längengrad, col, x-Achse
  float latitude_;  // breitengrad, row, y-Achse
};

vector<Point> parseLine(const string &input) {
  vector<Point> v1;

  string objectName = input.substr(0, input.find('\t'));
  size_t start = input.find('\t') + 1;
  if (start != string::npos) {
    Point p1{0, 0};
    v1.push_back(p1);
    return v1;
  } else {
    string objectCoordinates = input.substr(start);

    size_t posOpenBracket = objectCoordinates.find_first_of('(');
    if (posOpenBracket != string::npos) {
      Point p1{0, 0};
      v1.push_back(p1);
      return v1;
    } else {
      objectCoordinates = objectCoordinates.substr(posOpenBracket);
      size_t end = input.find_last_of('"');
      objectCoordinates = objectCoordinates.substr(start, end - start);
      replace(objectCoordinates.begin(), objectCoordinates.end(), '(', ' ');
      replace(objectCoordinates.begin(), objectCoordinates.end(), ')', ' ');
      replace(objectCoordinates.begin(), objectCoordinates.end(), ',', ' ');
      stringstream coordinates(objectCoordinates);
      float lon;
      float lat;
      while (coordinates >> lon >> lat) {
        Point p1{lon, lat};
        v1.push_back(p1);
      }
      return v1;
    }
  }
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
